/* partsim.c
 * ---------
 * Authors: Darwin Jacob Groskleg
 *
 *  Part I:  Ideal Gas Law Particle Simulation
 *  Part II: Brownian Motion Particle Simulation
 */
#include <mpi.h>
#include <stdlib.h>
#include <math.h>

#include "coordinate.h"
#include "definitions.h"
#include "physics.h"
#include "random.h"

// Developer's Config
#define SIM_TOTAL_TIME 100

#define VDIM  0   // VERTICAL_DIM
#define HDIM  1   // HORIZONTAL_DIM
enum Directions { Above, Below, Left, Right };
enum TaskRanks {
    SendTaskRank = 0
};

typedef struct Grid { int rows; int cols; } grid_t;
grid_t OptimalGrid(int subunits) {
    int k=sqrt(subunits);
    while (k>0 && subunits%k != 0)
        k--;
    return (grid_t) { .rows = k, .cols = subunits / k };
}

// 2D is implied by Box, ndims is not needed.
box_t BoxSubSection(box_t box, grid_t grid, int coords[2]) {
    float section_width  = box.width  / grid.cols;
    float section_height = box.height / grid.rows;
    return (box_t) {
        .width  = section_width,
        .height = section_height,
        .coord  = {
            .x0 = coords[HDIM] * section_width,
            .y0 = coords[VDIM] * section_height,
            .x1 = (coords[HDIM] == grid.cols-1)
                    ? box.width
                    : (coords[HDIM]+1) * section_width,
            .y1 = (coords[VDIM] == grid.rows-1)
                    ? box.height
                    : (coords[VDIM]+1) * section_height,
        }
    };
}

// Global temperature of the box
double GetChamberTemperature(double section_temperature, MPI_Comm comm) {
    double temp_sum = 0;
    MPI_Reduce(&section_temperature, &temp_sum, 1, MPI_DOUBLE, MPI_SUM, 0,comm);
    int cluster_size;
    MPI_Comm_size(comm, &cluster_size);
    return temp_sum / TotalParticles(cluster_size);
}

// knows size, knows values, is monadic
// returns temperature
double GetRandomParticles(box_t box, particle_t **prtcl_arr) {
    *prtcl_arr = (particle_t*)malloc(ParticlesForSection()*sizeof(particle_t));
    double temperature=0;
    if (*prtcl_arr != NULL) {
        for (int i=0; i<ParticlesForSection(); i++) {
            *(*prtcl_arr+i) = ConstructRandomParticle(box);
            temperature += (*prtcl_arr+i)->temp_0;
        }
    }
    return temperature;
}
void SafeFree(void **pp){
    if (pp != NULL && *pp != NULL) {
        free(*pp);
        *pp = NULL;
    }
}

typedef struct NeighborBuffer {
    int sendb_size[4];
    int recvb_size[4];
    particle_t sendb[4][PARTICLE_BUFFER_SIZE];
    particle_t recvb[4][PARTICLE_BUFFER_SIZE];
} neighbor_buff_t;


int main(int argc, char *argv[]) {

    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int cluster_size;
    MPI_Comm_size(MPI_COMM_WORLD, &cluster_size);

    /// WHAT IS THE PARALLEL PATTERN?
    ///     - Divide and Conquer: divide 2D map into particle sub-systems,
    ///         one for each process.
    ///     - See Lecture 10: Partitioning, suggest D&C for N-body problems.
    ///     - Thus computation follows static load balancing, imbalance in the
    ///         distribution of particles more likely as time goes on.
    /// IS THERE A COMMUNICATION TOPOLOGY?
    ///     - Each process is a sub-section of the chamber, either think of this
    ///         recursively or have back and forth between a process and its 8
    ///         neighboring sections.
    /// HOW AND WHEN DO PROCESSES COMMUNICATE WITH ONE ANOTHER?
    ///     - Communication may either be coordinatedj
    /// WHO INITIALIZES WHAT PARTICLES?
    /// IS THERE AN MPI AWARE APPROACH TO RANDOM SEEDING REQUIRED?
    ///     - No but randomization library has been modified to allow seed
    ///         offsets.
    /// HOW MANY ACTUAL PARTICLES IF WE PLAN TO SCALE PROCESSOR COUNT?

// BUILD GLOBAL BOX
// Depends on:  cluster_size,

    // Greater system: chamber construction
    box_t chamber = {
        .width  = BOX_HORIZ_SIZE,
        .height = BOX_VERT_SIZE,
        .coord  = {
            .x0 = 0,    // left wall
            .y0 = 0,    // bottom wall
            .x1 = BOX_HORIZ_SIZE,   // right wall
            .y1 = BOX_VERT_SIZE
        }
    };

    // Setup Cartesian grid that the discretized particles will exist on.
    // Assuming the grid is square but subsections might be rectangular???
    //
    // We want the smallest grid size that is
    // divisible by the number of processors in our cluster. This optimizes for
    // 2 things: floating point number numerical limits and workload
    // divisibility, allowing the simulation's gas chamber to be easily divided
    // into subsections accross the cluster.
    grid_t grid = OptimalGrid(cluster_size);
    int dims[2];
    dims[VDIM] = grid.rows;
    dims[HDIM] = grid.cols;
    MPI_Dims_create(cluster_size, 2, dims);
    int periods[2] = {1, 1}; // both dims are periodic, world wrapping allowed
    int reorder = 1; // true
    MPI_Comm grid_comm;
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &grid_comm);


// BUILD LOCAL BOX
//  depends on:     grid, grid_comm

    // Get coordinates on grid assigned for current process rank
    int grid_section_coords[2];
    MPI_Cart_get(grid_comm, 2, dims, periods, grid_section_coords);

    // Chamber subsection for current rank
    //  require: chamber, grid, coords[2],
    box_t section = BoxSubSection(chamber, grid, grid_section_coords);

    // Get neighboring processor ranks
    int neighbors[4];
    MPI_Cart_shift(grid_comm, VDIM, 1, &neighbors[Below], &neighbors[Above]);
    MPI_Cart_shift(grid_comm, HDIM, 1, &neighbors[Left],  &neighbors[Right]);

    // Greater system: particle initialization?


    // Greater system: initial values for IGL Equation
    // R = 8.3145 joules/moles/kelvin

    // Seed the entropy server
    RandomizeWithOffset(rank);
    // Initiate particles.
    // TODO change this to a linked list
    particle_t *local_particles = NULL;
    typedef struct ParticleList {} ParticleList_t;
    ParticleList_t plist;
    double section_temp = GetRandomParticles(section, &local_particles);

    double temperature = GetChamberTemperature(section_temp, grid_comm);
    double section_pressure = 0.0;

    typedef struct ParticleCollision {
        particle_t *a;
        particle_t *b;
        // temperature???
        // time???
    } ParticleCollision_t;
    typedef struct CollisionList     {} CollisionList_t;

    neighbor_buff_t mailbox;

    // Each time-step do:
    //      - for all particles:
    //          - 1. check for collisions
    //          - 2. move particles not colliding
    //          - 3. check for wall interaction
    //               and add the momentum
    //      - Communicate if needed
    //
    // TIME == SPEED OF CAUSALITY
    for (int t=0; t<SIM_TOTAL_TIME; t++) {

        // Clean the mailbox: send and receivce buffers
        for (int direction=Above; direction<=Right; direction++) {

        }

        //// Iterating foreach-style over particles guarantees O(N^2)
        //for (node_t *part_ptr=plist.head; part_ptr!=NULL;
        //      part_ptr=part_ptr->next)
        //{

        // 1. Find collisions in local section of box

        /* FindCollisions
         * returns
         *      - A list of collisions between p_i and p_last,
         *          that can be appended to the greater collision list.
         *      - Mutates *particle_ptr to be the next particle in list
         *          whenever a collision is found.
         *      ASSUMES only 2 particles in a collision.
         *      - Removes colliding particles from the particle list,
         *          safely leaving others as 'non-colliding' particles.
         */
        //CollisionList_t collisions = FindCollisions(&part_ptr);

        /* ExtractCollisions
         *
         * RETURNS
         *  A list of collisions (pairs) between particles in the given list.
         *
         * MUTATES
         *  The given particle list, the colliding particles are removed.
         *
         * ASSUMES
         *  A collision only ever happens between 2 particles and no more.
         *
         * Complexity: O(N^2)
         */
        CollisionList_t collisions = ExtractCollisions(&plist);

        // 2. Move non-colliding particles
        StepTimeForward(&plist);

        // 3. Simulate collisions and add particles back to list
        //  MUTATION
        //      Collision list will be empty.
        StepCollisionsForward(&collisions, &plist);

        // 4. Check for wall interaction and add the momentum
        //  MUTATIONS
        //      Elements in plist will have their vectors changed to account for
        //      wall rebound.
        section_pressure += AdjustForWallPressure(chamber, &plist);

        // 5. Gather those particles thath have left this section of the chamber
        CollectSectionEmigrants(section, &plist, &mailbox);

        // 6. Send particles asynchronously
        MPI_Request isend_status[4];
        DispatchEmigrantParticles(&mailbox, &isend_status, grid_comm);

        // 7. Receive particles form neighboring sections, wait until done
        IntegrateImmigrantParticles(&plist, &mailbox, &isend_status, grid_comm);

    }
    // free(particleList)

    // Caculate final pressure.
    double pressure = GetChamberPressure(section_pressure, grid_comm);

    printf("Final pressure: %.3lf\n", pressure);

    MPI_Finalize();
    return 0;
}

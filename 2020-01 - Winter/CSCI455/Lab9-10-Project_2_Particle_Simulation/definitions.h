/* definitions.h
 * -------------
 * Purpose:
 *  For keeping all simulation assumptions and initial values given by the
 *  instructor in a single place. Any other assumptions not given by
 *  instruction will be listed elsewhere.
 */
//#include <stdlib.h>
//#include <math.h>
#include "coordinate.h"

#ifndef _definitions_h
#define _definitions_h

#ifndef PI
#define PI 3.141592653
#endif // PI

/// REQUIRED INITIAL VALUES (Section 2.3)

/// - Each time-step must be 1 time unit long.
///  1 time-step == 1 time unit long (seconds?)
#define TIME_STEP 1

#include "random.h"
#include <math.h>
/// - Particle vector initialization:
///   initial_velocity < 50 (m/s)
///   absolute_velocity = rand()
///     r = rand() * MAC_INITIAL_VELOCITY
///     theta_0 = rand() * 2*PI
///     vx_0 = r*cos(theta_0)
///     vy_0 = r*sin(theta_0)
#define MAX_INITIAL_VELOCITY  50
inline particle_t ConstructRandomParticle(box_t box){
    float r = RandomReal(0, MAX_INITIAL_VELOCITY);
    float theta = RandomReal(0, 2*PI);
    float vx_0 = r * cos(theta);
    float vy_0 = r * sin(theta);
    return (particle_t) {
        .pcoord.x  = RandomReal(box.coord.x0, box.coord.x1),
        .pcoord.y  = RandomReal(box.coord.y0, box.coord.y1),
        .pcoord.vx = vx_0,
        .pcoord.vy = vy_0,
        .temp_0 = (r*r) / 2 // from Maxwell's equations
    };
}
//extern pcoord_t ConstructRandomParticle(int seed);

/// - Particle count
///     Suggested 10,000 x processing_cluster_size in assignment.
///     Below sets Initial value.
///     So which is it.
///   Simulation must end if 30x initial particles end up in any processor's
///   sub-section.
#define MAX_NO_PARTICLES   15000  /* Maximum number of particles/processor */
#define INIT_NO_PARTICLES    500  /* Initial number of particles/processor */
inline int TotalParticles(int processor_count) {
    return processor_count * INIT_NO_PARTICLES;
}
inline int ParticlesForSection() {
    return INIT_NO_PARTICLES;
}
//inline int ParticlesForSection(int p_rank, int processor_count) {
//    p_rank++;   // dummy
//    processor_count++;  // dummy
//    return INIT_NO_PARTICLES;
//}

// Worst case Receiving, how many particles per buffer?
//  initial worst case: all in section,
//                      init_no_particles == 500
//  overall worst case: all particles in all sections end up in one, then move.
//                      NOT POSSIBLE.
//  actual worst case:  maxed particles from all 4 neighborsj,
//
#define PARTICLE_BUFFER_SIZE        MAX_NO_PARTICLES/5
// Worst case Sending: the max number of particles a process can hold.
//                      MAX_NO_PARTICLES
//                      == COMM_BUFFER_SIZE
// Worst case Recving: the max number of particles 
// IGNORE COMM_BUFFER_SIZE for our implementation
#define COMM_BUFFER_SIZE            5*PARTICLE_BUFFER_SIZE
inline int MoveBufferToList(particle_t *arr, int arr_size, list_t *ll) {
    // ASSERT
    // arr <= PARTICLE_BUffER_SIZE
    // ll->size  <= MAX_NO_PARTICLES
    while (arr_size--) {
        ParticleListAppend(ll, arr[arr_size] );
    }
    return arr_size;
}
inline int MoveParticleToBuffer(node_t *pnp, particle_t *arr, int *arr_size) {
    // ASSERT
    //      (*arr_size) < PARTICLE_BUFFER_SIZE
    if (pnp != NULL && arr != NULL && arr_size != NULL) {
        arr[*arr_size] = pnp->element;
        (*arr_size)++;
        ParticleListDeleteNode(pnp);
    }
}


/// - Area of Box: width x height = 10^4 x 10^4
#define BOX_HORIZ_SIZE 10000.0
#define BOX_VERT_SIZE  10000.0
#define WALL_LENGTH (2.0*BOX_HORIZ_SIZE+2.0*BOX_VERT_SIZE)


/// - The Big Particle (for optional Brownian motion simulation)

#endif  /* _definitions_h */

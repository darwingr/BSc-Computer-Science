/* data-type-4-struct.c
 * --------------------
 * Authors: Darwin Jacob Groskleg
 *
 * Struct Derived Data Type:
 *      a data type that represents a particle and distribute an array of such
 *      particles to all processes.
 */
#include <stdio.h>
#include "mpi.h"

#define NELEM 25

enum TaskRanks { SendTaskRank = 0 };

int main(int argc, char *argv[])  {
    typedef struct {
        float x, y, z;
        float velocity;

        int  n, type;
    } Particle;

    MPI_Init(&argc,&argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int cluster_size;
    MPI_Comm_size(MPI_COMM_WORLD, &cluster_size);

    // required variables
    int composed_type_count = 2; // float, int
    MPI_Datatype composed_types[2];
    int blockcounts[2]; // block by type

    // MPI_Aint type used to be consistent with syntax of
    // MPI_Type_extent routine
    MPI_Aint    offsets[2];
    MPI_Aint    extent;

    // Descriptions of the 4 MPI_FLOAT fields:
    //      x, y, z, velocity
    offsets[0] = 0;
    composed_types[0] = MPI_FLOAT;
    blockcounts[0] = 4;

    // Descriptions of the 2 MPI_INT fields:
    //      n, type
    // Must first figure offset by getting size of MPI_FLOAT
    // DEPRECATED CALL:
    //      MPI_Type_extent(MPI_FLOAT, &extent);
    MPI_Type_get_extent(MPI_FLOAT, &extent, &extent);
    offsets[1] = 4 * extent;
    composed_types[1] = MPI_INT;
    blockcounts[1] = 2;

    // define structured type and commit it
    MPI_Datatype particletype;
    // NOTE MPI_Type_struct is deprecated in MPI3 !
    //MPI_Type_struct(composed_type_count, blockcounts, offsets, composed_types,
    //                &particletype);
    MPI_Type_create_struct(composed_type_count, blockcounts, offsets,
                           composed_types, &particletype);
    MPI_Type_commit(&particletype);


    Particle particles[NELEM]; // starting set
    Particle p[NELEM];

    // task 0 initializes the particle array and then sends it to each task
    int tag=1;
    MPI_Status stat;
    if (rank == SendTaskRank) {
        for (int i=0; i<NELEM; i++) {
            particles[i].x        = i * 1.0;
            particles[i].y        = i * -1.0;
            particles[i].z        = i * 1.0;
            particles[i].velocity = 0.25;
            particles[i].n    = i;
            particles[i].type = i % 2;
        }
        for (int dest_rank=0; dest_rank<cluster_size; dest_rank++)
            MPI_Send(particles, NELEM, particletype, dest_rank, tag,
                    MPI_COMM_WORLD);
    }

    // all tasks receive particletype data
    MPI_Recv(p, NELEM, particletype, SendTaskRank, tag, MPI_COMM_WORLD, &stat);

    printf("rank=%d   p{ %3.2f %3.2f %3.2f %3.2f   %d %d }\n",
            rank,   p[3].x, p[3].y, p[3].z, p[3].velocity, p[3].n, p[3].type);

    // free datatype when done using it
    MPI_Type_free(&particletype);
    MPI_Finalize();
    return 0;
}

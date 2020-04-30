/* data-type-3-indexed.c
 * ---------------------
 * Authors: Darwin Jacob Groskleg
 *
 * Index Derived Data Type:
 *      a datatype to extract variable portions of an array and then distribute
 *      to them to all tasks.
 */
#include <stdio.h>
#include "mpi.h"

#define A_SET_SIZE 16
#define B_SET_SIZE 6     // subset of A
#define BLOCKCOUNT 2

enum TaskRanks { SendTaskRank = 0 };

int main(int argc, char *argv[])  {
    float a[A_SET_SIZE] = {
         1.0,  2.0,  3.0,  4.0,
         5.0,  6.0,  7.0,  8.0,
         9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0
    };
    float b[B_SET_SIZE];     // subset of A


    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int cluster_size;
    MPI_Comm_size(MPI_COMM_WORLD, &cluster_size);

    const int blockcount = BLOCKCOUNT;
    int  blocklengths[BLOCKCOUNT] = { 4,  2 };
    int displacements[BLOCKCOUNT] = { 5, 12 };
    blocklengths[0] = 4;
    blocklengths[1] = 2;
    displacements[0] = 5;
    displacements[1] = 12;

    // create indexed derived data type
    MPI_Datatype indexedtype;
    MPI_Type_indexed(blockcount, blocklengths, displacements, MPI_FLOAT,
                    &indexedtype);
    MPI_Type_commit(&indexedtype);

    int tag=1;
    if (rank == SendTaskRank) {
        for (int dest_rank=0; dest_rank<cluster_size; dest_rank++)
            // task 0 sends one element of indexedtype to all tasks
            MPI_Send(
                &a,
                1,      // count of indexedtype
                indexedtype,
                dest_rank,
                tag,
                MPI_COMM_WORLD);
    }

    // all tasks receive indexedtype data from task 0
    MPI_Status stat;
    MPI_Recv(&b,
            B_SET_SIZE,     // target buffer size
            MPI_FLOAT,
            SendTaskRank,
            tag,
            MPI_COMM_WORLD,
            &stat);
    printf("rank=%d  b={ %3.1f %3.1f %3.1f %3.1f %3.1f %3.1f }\n",
                 rank,   b[0], b[1], b[2], b[3], b[4], b[5]);

    // free datatype when done using it
    MPI_Type_free(&indexedtype);
    MPI_Finalize();
    return 0;
}

/* data-type-1-contiguous.c
 * ------------------------
 * Authors: Darwin Jacob Groskleg
 *
 * Contiguous Derived Data Type:
 *      a data type representing a row of an array and distribute a different
 *      row to all processes.
 */
#include <stdio.h>
#include <mpi.h>

#define DATA_SET_WIDTH 4

enum TaskRanks { SendTaskRank = 0 };

int main(int argc, char *argv[]) {
    float a[DATA_SET_WIDTH][DATA_SET_WIDTH] = {
        { 1.0,  2.0,  3.0,  4.0},
        { 5.0,  6.0,  7.0,  8.0},
        { 9.0, 10.0, 11.0, 12.0},
        {13.0, 14.0, 15.0, 16.0}
    };
    float b[DATA_SET_WIDTH];

    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int cluster_size;
    MPI_Comm_size(MPI_COMM_WORLD, &cluster_size);

    // create contiguous derived data type
    MPI_Datatype rowtype;   // required variable
    MPI_Type_contiguous(DATA_SET_WIDTH, MPI_FLOAT, &rowtype);
    MPI_Type_commit(&rowtype);

    if (cluster_size == DATA_SET_WIDTH) {
        int tag=1;
        if (rank == SendTaskRank) {
            for (int i=0; i<cluster_size; i++)
                MPI_Send(
                    &a[i][0],   // send the i'th row
                    1,          // rows to send
                    rowtype,
                    i,          // destination rank
                    tag,
                    MPI_COMM_WORLD);
        }

        // all tasks receive rowtype data from task 0
        MPI_Status stat;
        MPI_Recv(
            &b,
            1,              // rows received
            rowtype,
            SendTaskRank,   // from master rank
            tag,
            MPI_COMM_WORLD,
            &stat);
        printf("rank=%d  b={ %4.1f %4.1f %4.1f %4.1f }\n",
                     rank,   b[0], b[1], b[2], b[3]);
    }
    else
        printf("Must specify %d processors. Terminating.\n", DATA_SET_WIDTH);

    // free datatype when done using it
    MPI_Type_free(&rowtype);
    MPI_Finalize();
    return 0;
}

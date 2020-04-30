/* data-type-2-vector.c
 * --------------------
 * Authors: Darwin Jacob Groskleg
 *
 * Vector Derived Data Type:
 *       a data type representing a column of an array and distribute
 *       different columns to all processes.
 */
#include <stdio.h>
#include <mpi.h>

#define DATA_SET_WIDTH 4

enum TaskRanks { SendTaskRank = 0 };

int main(int argc, char *argv[])  {
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

    //if (rank == SendTaskRank) {
    //    printf("a={ %.1f",    *(a[0] + 0));
    //    for (int i=0; i<DATA_SET_WIDTH*DATA_SET_WIDTH; i++)
    //        printf(", %.1f", *(a[0] + i));
    //    printf(" }\n");
    //}
    //MPI_Barrier(MPI_COMM_WORLD);

    // create vector derived data type
    MPI_Datatype columntype;   // required variable
    int count       = DATA_SET_WIDTH;   // count of elements of type float
    int blocklength = 1;
    int stride      = DATA_SET_WIDTH;
    // strided contiguous data type
    MPI_Type_vector(count, blocklength, stride, MPI_FLOAT, &columntype);
    MPI_Type_commit(&columntype);

    if (cluster_size == DATA_SET_WIDTH) {
        int tag=1;
        MPI_Status stat;
        // task 0 sends one element of columntype to all tasks
        if (rank == SendTaskRank) {
            for (int i=0; i<cluster_size; i++)
                MPI_Send(
                    &a[0][i],   // send i'th column
                    1,          // columns being sent
                    columntype,
                    i,          // destination rank
                    tag,
                    MPI_COMM_WORLD);
        }

        // all tasks receive columntype data from task 0
        MPI_Recv(
            &b,
            DATA_SET_WIDTH,          // columns received
            MPI_FLOAT,
            SendTaskRank,
            tag,
            MPI_COMM_WORLD,
            &stat);
        printf("rank=%d  b={ %3.1f, %3.1f, %4.1f, %4.1f }\n",
                     rank,    b[0],  b[1],  b[2],  b[3]);
    }
    else
        printf("Must specify %d processors. Terminating.\n", DATA_SET_WIDTH);

    // free datatype when done using it
    MPI_Type_free(&columntype);
    MPI_Finalize();
    return 0;
}

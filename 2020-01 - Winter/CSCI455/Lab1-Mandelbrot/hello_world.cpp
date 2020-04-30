/* hello_world.cpp
 * ---------------
 * Authors: Darwin Jacob Groskleg, Laurence T. Yang
 * CSCI 455 Lab 1
 *
 * Purpose:  Print a greeting to the root processor, then all processors.
 *
 * Question: Can you complete the following “Hello World”” program and
 *           run with 4, 8 and 16 CPU processors?
 */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>    /* MPI header file */

int main(int argc, char *argv[]) {
    // Initialize for MPI
    //  (must come before any other calls to MPI routines)
    //  will initialize MPI_COMM_WORLD, a global declared in mpi.h
    MPI_Init(&argc, &argv);

    // Get number of processes,
    //  sets it to nproc
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    // Get this process's number (ranges from 0 to nprocs - 1)
    //  sets it to myid
    int myid;
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    // Please print a greeting with the root processor and all processors,
    //  respectively.
    // Therefore must use SPMD(single program,multi-device) computational model.
    if (myid == 0) { // is root
        printf("Hello world! From the root processor!\n");
    }
    // Block so root prints before all.
    MPI_Barrier(MPI_COMM_WORLD);
    // int fake_data = 0;
    //MPI_Recv(&fake_data, 0, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD,
    //          MPI_STATUS_IGNORE)
    // Now from all processors
    printf("Hello world! From processor %d of %d.\n", myid+1, nprocs);


    // Clean up for MPI
    //  (should come after all other calls to MPI routines)
    MPI_Finalize();

    return EXIT_SUCCESS;
}

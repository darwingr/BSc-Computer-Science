/* parsum.c
 * --------
 * Authors: Darwin Jacob Groskleg, Laurence T. Yang
 * CSCI 455
 * Lab #2: Parallel Sum
 *
 * Purpose: compute the sum of numbers read in from a file by distributing the
 *          computation in blocks of 100 numbers over the processors.
 *
 *          Uses the "Broadcast/Reduce Routine", see Lecture 10, for
 *          partitioning the summation.
 *
 * TODO:
 *  - [x] Fill in all missing parts of the code.
 *  - [x] Should find out the number of processors in the cluster and divide the
 *        work evenly among them instead of assuming it has 10 processors doing
 *        100 numbers each.
 *  - [ ] Modify the program so that it also computes the MIN and MAX values of
 *        the data read in.
 *        Tips: you'll write your own min/max routines that find the min/max of
 *        each block of numbers, and then have a call to MPI reduce that finds
 *        the min/max of all the "partial" results.
 */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#include <mpi.h>
#include "trace.h"

#define MAXSIZE 1000  // original limit
//#define MAXSIZE 100000
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

/* Initialize with a limit state. */
typedef struct {
    int sum;
    int min;
    int max;
} range_sum_t;

range_sum_t minmaxadd(int *A, int low, int high);
int add(int *A, int low, int high);
int sign(int z);
int div_out(int num, int denom);
void show_usage(char* program);

int myid, cluster_size;

int main(int argc, char *argv[]) {
    /* 4 Synchronized variables, requiring broadcasts from root */
    int set_size = 0;
    int data[MAXSIZE];
    int max_partition_size;
    bool file_contains_data = true;

    MPI_Init(&argc, &argv);                         /* Initialize MPI */
    MPI_Comm_size(MPI_COMM_WORLD, &cluster_size);   /* Find group size */
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);           /* Find process rank */
    bool root_process = (myid == 0);

    /* Root: open the data file */
    char* datafilename = argv[1];
    FILE *fp;   /* file pointer, initialized by fopen */
    if (root_process) {
        if (argc != 2)
            show_usage(argv[0]);
        TRACE("starting");

        TRACE("opening data file \n");
        /* Open Input File and Initialize Data Array */
        if ((fp = fopen(datafilename,"r")) == NULL) {
            printf("Can't open the input file: %s\n\n", datafilename);
            MPI_Abort(MPI_COMM_WORLD, 1);
            exit(1);
        }
    }

    /* only important to root */
    long long global_sum = 0;
    while (file_contains_data) {
        /* Root Proc: copy numbers to an array from open data file. */
        if (root_process) {
            for(set_size=0; set_size<MAXSIZE && !feof(fp); set_size++)
                fscanf(fp,"%d", &data[set_size]);

            if (feof(fp)) {
                TRACE("Reached end of data file, closing.\nAll ");
                fclose(fp);
                file_contains_data = false;
            }
            TRACE("data is read.\n");
            max_partition_size = div_out(set_size, cluster_size);
        }


        /* Broadcast the partition size and data to all node processes */
        if (root_process)
            TRACE("calling MPI_Bcast\n");
        MPI_Bcast( &file_contains_data,       1, MPI_C_BOOL, 0, MPI_COMM_WORLD);
        MPI_Bcast( &set_size,                 1,    MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast( &max_partition_size,       1,    MPI_INT, 0, MPI_COMM_WORLD);
        /* Bcast data[] */
        MPI_Bcast(               &data, set_size,   MPI_INT, 0, MPI_COMM_WORLD);
        if (root_process)
            TRACE("MPI_Bcast done \n");


        /* Do the calculating: sum and reduce */
        MPI_Barrier(MPI_COMM_WORLD);
        /* Calculate the low and high index for each processor */
        int low_i, high_i;
        low_i  = myid * max_partition_size;
        high_i = MIN(low_i + max_partition_size, set_size) - 1;

        /* Local addition for all processes */
        if (root_process)
            TRACE("adding...\n");
        long long node_sum = add(data, low_i, high_i);
        printf("I got %lld from node %d\n", node_sum, myid);
        MPI_Barrier(MPI_COMM_WORLD);

        /* Global reduce */
        if (root_process) {
            TRACE("calling reduce...\n");
        }
        /* MPI_Reduce(
         *     void* send_data,
         *     void* recv_data,
         *     int count,
         *     MPI_Datatype datatype,
         *     MPI_Op op,
         *     int root,
         *     MPI_Comm communicator)
         */
        MPI_Reduce( // Sum operation
                &node_sum,
                &global_sum,    // receiver
                1,  // count of elements in the recv/send arrays
                MPI_LONG_LONG,
                MPI_SUM,
                0,  // root rank
                MPI_COMM_WORLD);
        if (root_process)
            printf("The sum is %lld.\n", global_sum);
    }

    /* MPI finalize */
    MPI_Finalize();
    return EXIT_SUCCESS;
}


void show_usage(char* program) {
    printf("Usage: %s path/to/datafile.txt\n", program);
    MPI_Abort(MPI_COMM_WORLD, 1);
    exit(1);
}

range_sum_t minmaxadd(int *A, int low, int high) {
    range_sum_t res = {0, INT_MAX, INT_MIN};
    for (int i=low; i<=high; i++) {
        res.sum += A[i];
        res.min = MIN(res.min, A[i]);
        res.max = MAX(res.max, A[i]);
    }
    return res;
}

/* Adds range within an array,
 *  between positions low and high, inclusive.
 */
int add(int *A, int low, int high) {
    int res = 0;
    for (int i=low; i<=high; i++)
        res += A[i];
    return res;
}

/*
 * Give me a sign!
 *  Range: (-1, 0, 1)
 */
int sign(int z) {
    return ((0 < z) - (z < 0));
}

/* Integer division '/', in C99 and up, truncates towards zero.
 * We want to round away from zero so that we can ___ 
 * when deciding how many numbers to give to each node for summation.
 *
 *  int div in VS. int div out
 */
int div_out(int num, int denom) {
    div_t divresult = div(num, denom);
    return num/denom + sign(divresult.rem);
}


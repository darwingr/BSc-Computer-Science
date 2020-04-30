/******************************************************************************
* FILE: mpi_latency.c
* AUTHORS:
*   Darwin Jacob Groskleg (2020)
*   Sazzad (02/11/18)
*   Laurence T. Yang
* DESCRIPTION:
*   MPI Latency Timing Program - C Version
*   In this example code, a MPI communication timing test is performed.
*   MPI process 0 will send "reps" number of 1 byte messages to MPI process 1,
*   waiting for a reply between each rep. Before and after timings are made 
*   for each rep and an average calculated when completed.
*
* NOTES
*   - Ping-pong method sends same size data back and forth.
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#include <sys/time.h>
#include <mpi.h>

#include "slr.h"

#define NUMBER_REPS 10
#define DATA_SIZE 5000

/* send/receive process designators, maps task label to expected rank */
enum TaskRanks {
    Master = 0,
    Worker = 1
};

double sample_latency_with_n_bytes(int bytes_of_traffic);
void run_sampling_responder(int bytes_of_traffic);

/*
 * Estimate the t_startup and t_data with the least square regression method:
 *  y: AvgT/2 (one way latency)
 *  let K = 10 (number of runs, different message sizes)
 * t_startup = m * 0 + b            (time to send msg with no data)
 * t_comm = m*1 + b                 (time to startup and send 1 data word)
 * t_data = t_comm - t_startup   (time to send one data word)
 */
int main (int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int cluster_size;           /* number of MPI processes */
    MPI_Comm_size(MPI_COMM_WORLD, &cluster_size);
    int rank;                   /* my MPI process number */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == Master && cluster_size != 2) {
        printf("INFO: Number of processes = %d\n", cluster_size);
        printf("INFO: Only executing 2 tasks - extra cluster processes ");
        printf("will be ignored\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);

    if (rank < 2) {
        printf("task %d has started...\n", rank);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    int x_byte_counts[] = {10, 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000};
    size_t k_tests = sizeof(x_byte_counts)/sizeof(x_byte_counts[0]);
    double y_timings[k_tests];

    for (size_t i=0; i<k_tests; i++){
        if (rank == Worker) {
            run_sampling_responder(x_byte_counts[i]);
        }
        else if (rank == Master) {
            y_timings[i] = sample_latency_with_n_bytes(x_byte_counts[i]);
        }
    }

    if (rank == Master) {
        slr_equation_t eqt = slr_find_line(k_tests, x_byte_counts, y_timings);
        double t_startup = slr_predict(eqt, 0);
        double t_comm    = slr_predict(eqt, 1);
        double t_data    = t_comm - t_startup;
        printf("SUMMARY STATISTICS/ESTIMATIONS:\n");
        printf("t_comm(1) = %f microseconds\n", t_comm);
        printf("t_startup = %f microseconds\n", t_startup);
        printf("t_data    = %f microseconds\n", t_data);
    }

    MPI_Finalize();
    exit(0);
}

/* Returns: time in microseconds (t_comm)
 *      - the one-way latency (round-trip / 2)
 * Takes:
 *  bytes_of_traffic = N, the amount of data to be sent
 */
double sample_latency_with_n_bytes(int bytes_of_traffic) {
    assert(bytes_of_traffic <= DATA_SIZE);

    char msg[DATA_SIZE];        /* buffer containing DATA_SIZE byte message */
    MPI_Status status;          /* MPI receive routine parameter */
    int tag = 1;                /* MPI message tag parameter */
    int reps = NUMBER_REPS;     /* number of samples per test */
    /* round-trip latency timing test */
    printf("Beginning latency timing test:\n");
    printf("\tNumber of reps = %d\n", reps);
    printf("\tData Size      = %d\n", bytes_of_traffic);
    printf("****************************************\n");
    /*      <  >  <      . >  <      . >  <      . >                      */
    printf("Rep#       T0          T1         deltaT\n");

    const double MSPerSecond = pow(10, 6);
    const double ClockResolution = 1;//MPI_Wtick(); // seconds per clock tick
    double T0, T1;              /* start/end times per rep in ms */
    double deltaT;              /* time for one rep in ms */
    double sumT = 0;            /* sum of all reps times in microseconds */
    int error;
    for (int n = 1; n <= reps; n++) {
        /* start time */
        T0 = MPI_Wtime() * MSPerSecond * ClockResolution;

        /* send message to worker - message tag set to 1.  */
        error = MPI_Send(
                &msg,
                bytes_of_traffic,
                MPI_BYTE,   // for char
                Worker,     // destination
                tag,
                MPI_COMM_WORLD
            );
        /* If return code indicates error quit */
        // DARWIN GROSKLEG:
        //  this is unecessary and already properly handled
        //  by the MPI error handler, which will abort the MPI job in most
        //  cases.
        if (error)
            MPI_Abort(MPI_COMM_WORLD, error);

        /* Now wait to receive the echo reply from the worker  */
        // "echoes" the same data back???
        error = MPI_Recv(
            &msg,
            bytes_of_traffic,
            MPI_BYTE,   // for char
            Worker,     // source
            tag,
            MPI_COMM_WORLD,
            &status);

        /* If return code indicates error quit */
        // Redundant step is skipped because the MPI already handles it.
        if (error)
            MPI_Abort(MPI_COMM_WORLD, error);

        /* end time */
        T1 = MPI_Wtime() * MSPerSecond * ClockResolution;

        /* calculate round trip time and print */
        deltaT = T1 - T0;
        sumT += deltaT;
        /* print statement for each to keep each column right justified */
        printf("%4d  ", n);
        printf("%10.2f  ", T0);
        printf("%10.2f  ", T1);
        printf("%10.2f\n", deltaT);
    }

    /* average time per rep in microseconds */
    double avgT = sumT / reps;
    printf("****************************************\n");
    printf("*** Avg round trip time = %f microseconds\n", avgT);
    printf("*** Avg one way latency = %f microseconds\n", avgT/2);

    return avgT/2;
}

void run_sampling_responder(int bytes_of_traffic) {
    assert(bytes_of_traffic <= DATA_SIZE);
    char msg[DATA_SIZE];        /* buffer containing DATA_SIZE byte message */
    MPI_Status status;          /* MPI receive routine parameter */
    int tag = 1;                /* MPI message tag parameter */
    int reps = NUMBER_REPS;     /* number of samples per test */

    while (reps--) {
        // ping
        MPI_Recv(
            &msg,
            bytes_of_traffic,
            MPI_BYTE,
            Master,
            tag,
            MPI_COMM_WORLD,
            &status);
        // pong
        MPI_Send(
            &msg,
            bytes_of_traffic,
            MPI_BYTE,
            Master,
            tag,
            MPI_COMM_WORLD);
    }
}

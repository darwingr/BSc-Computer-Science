/* parpi.c
 * -------
 * Authors: Darwin Jacob Groskleg
 * CSCI 455
 * Lab 3 - Calculation of Pi
 *
 * Purpose: to determine the value of pi. The lab uses the method to evaluate
 *          the integral of 4/(1+x*x) between 0 and 1.
 *
 * See 'lecture09-Ch3-Embarassingly Parallel.ppt' for algorithm details.
 *
 * TODO:
 *  - [x] Complete the skeleton code.
 *  - [x] Can you run the code with 5, 10, 20, 40, 60 or more processors,
 *        respectively, to see the speedups? Do you see any unusual changes on
 *        speedup?
 *  - [x] Can you double the NUM_STEPS with the same number of processors as
 *        above, then compare and observe the speed ups?
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <locale.h>

#include <mpi.h>

#ifndef M_PI
/* copied from not-strictly-standard part of math.h */
#define M_PI    3.14159265358979323846
#endif  /* M_PI */

#define BASE_NUM_STEPS 400000000
int NUM_STEPS = BASE_NUM_STEPS;

int main(int argc, char *argv[]) {
    /* initialize for MPI */
    MPI_Init(&argc, &argv);

    if (argc>1)
        NUM_STEPS *= atoi(argv[1]);

    /* get number of processes */
    int cluster_size;
    MPI_Comm_size(MPI_COMM_WORLD, &cluster_size);

    /* get this process's number (ranges from 0 to cluster_size - 1) */
    int myid;
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    /* record start time */
    double start_time = MPI_Wtime();

    /* do computation */
    double step = 1.0/(double) NUM_STEPS;
    double x;
    double sum = 0.0;
    for (int i=myid+1; i<=NUM_STEPS; i+=cluster_size) {
        x = step * ((double) i - 0.5);
        sum += 4.0 / (1.0 + x*x);
    }
    double piece_of_pi = step * sum;
    double pi = 0.0;
    MPI_Reduce(
            &piece_of_pi,
            &pi,    // receiver
            1,      // data count
            MPI_DOUBLE,
            MPI_SUM,
            0,      // root node rank (receiver)
            MPI_COMM_WORLD
        );

    /* record end time */
    double end_time = MPI_Wtime();
    double seconds_per_tick = MPI_Wtick();
    double seconds_elapsed = (end_time - start_time) * seconds_per_tick;

    /* print results */
    if (myid == 0) {
        setlocale(LC_NUMERIC, ""); /* thousand separator for easy reading  */
        printf("parallel program results with %'d processes and %'d steps:\n",
                cluster_size, NUM_STEPS);
        printf("computed pi = %g  (%'17.15f)\n",pi, pi);
        long double delta_err = fabs(pi - M_PI);
        printf("difference between computed pi and math.h M_PI = ");
        printf("%'17.15Lf (%1.2Le)\n", delta_err, delta_err);
        printf("time to compute = %g seconds\n", seconds_elapsed);
    }

    /* clean up for MPI */
    MPI_Finalize();

    return 0;
}

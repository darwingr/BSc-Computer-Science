/* hiding_latency.c
 * ----------------
 * Authors: Darwin Jacob Groskleg
 * Date:    Saturday, May 16, 2020
 *
 * Taken from "Intro to Parallel Computing (2018), Roman Trobec et al.",
 *  Page 120
 *
 * Overlapping communication and computation
 */
#include <mpi.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
int i; double a;
for (i = 0; i < 100000000/numproc; i++) {
a = sin(sqrt(i)); //different amount of calculation return a;
main(int argc, char* argv[]) //number of processes must be > 1
int p, i, myid, tag=1, proc, ierr;
double start_p, run_time, start_c, comm_t, start_w, work_t, work_r; double *buff = nullptr;
MPI_Request request; MPI_Status status;
MPI_Init(&argc, &argv);
start_p = MPI_Wtime(); MPI_Comm_rank(MPI_COMM_WORLD, &myid); MPI_Comm_size(MPI_COMM_WORLD, &p);
#define master 0
#define MSGSIZE 100000000 //5000000 //different sizes of ← 
messages
buff = (double*)malloc(MSGSIZE * sizeof(double)); //allocate
if (myid == master) {
for (i = 0; i < MSGSIZE; i++) { //initialize message
buff[i] = 1;
}
start_c = MPI_Wtime();
for (proc = 1; proc<p; proc++) {
MPI_Irecv(buff, MSGSIZE,
MPI_DOUBLE, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &← 
      1
2
3
4 5{ 6
   double other_work(int numproc)
   7
8 9}
   10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28
29 30 31 32 33 34 35 36 37 38 39
40 41 42 43
44 45 46 47 48 49 50 51
}
int {
                            #if 1
 //non-blocking receive
  request); #endif
  #if 0
); #endif
}
MPI_Recv(buff, MSGSIZE, //blocking receive
MPI_DOUBLE, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status← 
     }
comm_t = MPI_Wtime() - start_c; start_w = MPI_Wtime();
work_r = other_work(p);
work_t = MPI_Wtime() - start_w; MPI_Wait(&request, &status);
//block until Irecv is done
      

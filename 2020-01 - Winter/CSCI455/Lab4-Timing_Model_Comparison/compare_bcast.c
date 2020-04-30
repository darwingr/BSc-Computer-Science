//
// Comparison of MPI_Bcast with the my_bcast function
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <mpi.h>

/* send/receive process designators, maps task label to expected rank */
enum TaskRanks {
    Master = 0,
    Worker = 1
};

void my_bcast(void* data, int count, MPI_Datatype datatype, int root,
              MPI_Comm communicator)
{
    int world_rank;
    MPI_Comm_rank(communicator, &world_rank);
    int world_size;
    MPI_Comm_size(communicator, &world_size);

    if (world_rank == root) {
        // If we are the root process, send our data to everyone


    } else {
        // If we are a receiver process, receive the data from the root


    }
}

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: compare_bcast num_elements num_trials\n");
        exit(1);
    }

    int num_elements = atoi(argv[1]);
    int num_trials = atoi(argv[2]);

    MPI_Init(NULL, NULL);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    double total_my_bcast_time = 0.0;
    double total_mpi_bcast_time = 0.0;
    int i;
    int* data = (int*)malloc(sizeof(int) * num_elements);
    assert(data != NULL);

    for (i = 0; i < num_trials; i++) {
        // Time my_bcast
        // Synchronize before starting timing



        // Synchronize again before obtaining final time



        // Time MPI_Bcast



    }

    // Print off timing information
    if (world_rank == 0) {
        printf("Data size = %d, Trials = %d\n", num_elements * (int)sizeof(int),
            num_trials);
        printf("Avg my_bcast time = %lf\n", total_my_bcast_time / num_trials);
        printf("Avg MPI_Bcast time = %lf\n", total_mpi_bcast_time / num_trials);
    }

    free(data);
    MPI_Finalize();
    return 0;
}

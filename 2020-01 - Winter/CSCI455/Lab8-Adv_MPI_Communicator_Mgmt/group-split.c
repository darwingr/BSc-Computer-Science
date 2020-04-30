#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int numprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    /* Color of local process:
     *  decides to which communicator the process will
     *  belong after the split.
     */
    int color = world_rank % 2;

    // Communicator split is a remote opration?
    MPI_Comm New_Comm;
    MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &New_Comm);
    int new_rank;
    MPI_Comm_rank(New_Comm, &new_rank);
    int new_nodes;
    MPI_Comm_size(New_Comm, &new_nodes);

    int broad_val;
    if(new_rank == 0)
        broad_val = color;
    MPI_Bcast(&broad_val, 1, MPI_INT, 0, New_Comm);

    printf("Old_proc [%d] has new rank [%d], received value %d\n",
              world_rank,          new_rank,           broad_val);

    MPI_Comm_free(&New_Comm);
    MPI_Finalize();
    return 0;
}

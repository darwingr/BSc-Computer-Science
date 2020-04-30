#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define NPROCS 8

int main(int argc, char *argv[])  {
    MPI_Init(&argc,&argv);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int numtasks;
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    if (numtasks != NPROCS) {
        printf("Must specify MP_PROCS= %d. Terminating.\n",NPROCS);
        MPI_Finalize();
        exit(0);
    }

    // extract the original group handle
    MPI_Group  orig_group;
    MPI_Comm_group(MPI_COMM_WORLD, &orig_group);
    MPI_Group  new_group;

    //  divide tasks into two distinct groups based upon world_rank
    //  Group Contruction: happens locally.
    if (world_rank < NPROCS/2) {
        const int ranks1[4]={0,1,2,3};
        MPI_Group_incl(orig_group, 4, ranks1, &new_group);
    }
    else {
        const int ranks2[4]={4,5,6,7};
        MPI_Group_incl(orig_group, 4, ranks2, &new_group);
    }

    // create new new communicator and then perform collective communications
    // Communicator Construction: happens remotely/collectively.
    MPI_Comm   new_comm;
    MPI_Comm_create(MPI_COMM_WORLD, new_group, &new_comm);

    int sendbuf = world_rank;
    int recvbuf;
    MPI_Allreduce(&sendbuf, &recvbuf, 1, MPI_INT, MPI_SUM, new_comm);

    // get rank in new group
    int new_rank;
    MPI_Group_rank(new_group, &new_rank);


    printf("rank = %d  newrank = %d  recvbuf= %d\n",
           world_rank,     new_rank,     recvbuf);


    MPI_Group_free(&orig_group);
    MPI_Group_free(&new_group);
    MPI_Comm_free(&new_comm);
    MPI_Finalize();
    return 0;
}

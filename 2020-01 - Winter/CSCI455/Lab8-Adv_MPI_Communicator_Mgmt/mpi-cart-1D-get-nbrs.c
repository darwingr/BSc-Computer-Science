/* mpi-cart-1D-get-nbrs.c
 * ----------------------
 * 1 Dimensional Cartesian Virtual Topology
 *  finds the neighbors in a cartesian communicator
 */
#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum { false, true } bool;

int main( int argc, char *argv[] ) {
    MPI_Init( &argc, &argv );
    int cluster_size;
    MPI_Comm_size( MPI_COMM_WORLD, &cluster_size );
    int rank;
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );

    const int ndims = 1;
    int dims[ndims];
    /* processor dimensions */
    dims[0] = cluster_size;
    /* create Cartesian topology for processes */
    //      nnodes, ndims, dims[]
    MPI_Dims_create(cluster_size, ndims, dims);

    if(rank == 0)
        printf("PW[%d]/[%d]: NDims=%d, PEdims = [%d]\n",
                rank, cluster_size, ndims,  dims[0]);

    int periods[ndims];
    int source, dest;
    bool reorder = true;
    MPI_Comm comm1D;

    /*************************************************************/
    /* Create periodic shift */
    /*************************************************************/
    /* periodic shift is true. */
    periods[0] = true;
    /* create Cartesian mapping */
    MPI_Cart_create(MPI_COMM_WORLD, ndims, dims, periods, reorder, &comm1D);

    //int errs = 0;
    MPI_Cart_shift(comm1D, dims[0], 1, &source, &dest);
    printf( "P[%d]:     periodic: shift  1: src[%d] P[%d] dest[%d]\n",
             rank,                      source, rank,    dest );
    fflush(stdout);

    MPI_Cart_shift(comm1D, dims[0], 0, &source, &dest);
    printf( "P[%d]:     periodic: shift  0: src[%d] P[%d] dest[%d]\n",
             rank,                      source, rank,    dest );
    fflush(stdout);

    MPI_Cart_shift(comm1D, dims[0], -1, &source, &dest);
    printf( "P[%d]:     periodic: shift -1: src[%d] P[%d] dest[%d]\n",
             rank,                      source, rank,    dest );
    fflush(stdout);
    MPI_Comm_free( &comm1D );

    /*************************************************************/
    /* Create non-periodic shift */
    /*************************************************************/
    if (rank == 0)
        printf("\nNon-periodic next\n");
    /* periodic shift is false. */
    periods[0] = false;
    MPI_Cart_create(MPI_COMM_WORLD, ndims, dims, periods, reorder, &comm1D);

    MPI_Cart_shift(comm1D, dims[0], 1, &source, &dest);
    printf( "P[%d]: non-periodic: shift  1: src[%d] P[%d] dest[%d]\n",
             rank,                      source, rank,    dest );
    fflush(stdout);
    MPI_Cart_shift(comm1D, dims[0], 0, &source, &dest);
    printf( "P[%d]: non-periodic: shift  0: src[%d] P[%d] dest[%d]\n",
             rank,                      source, rank,    dest );
    fflush(stdout);
    MPI_Cart_shift(comm1D, dims[0], -1, &source, &dest);
    printf( "P[%d]: non-periodic: shift -1: src[%d] P[%d] dest[%d]\n",
             rank,                      source, rank,    dest );
    fflush(stdout);
    MPI_Comm_free( &comm1D );

    MPI_Finalize();
    return 0;
}

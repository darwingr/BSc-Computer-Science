/* mpi-cart-2D-get-nbrs.c
 * ----------------------
 * 2 Dimensional Cartesian Virtual Topology
 *  finds the neighbors in a cartesian communicator
 */
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SHIFT_ROW 0
#define SHIFT_COL 1
#define DISP 1

typedef enum { false, true } bool;

int wrap_row(int  row_width, int col);
int wrap_col(int col_height, int row);

int main(int argc, char *argv[]) {
    //int errs;

    /* start up initial MPI environment */
    MPI_Init(&argc, &argv);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int ndims=2;
    int dims[ndims];
    int nrows;
    int ncols;

    /* process command line arguments*/
    if (argc == 3) {
        nrows = atoi (argv[1]);
        ncols = atoi (argv[2]);
        dims[0] = nrows; /* number of rows */
        dims[1] = ncols; /* number of columns */
        if( (nrows*ncols) != size) {
            if( my_rank ==0)
                printf("ERROR: nrows*ncols) = %d * %d = %d != %d\n",
                        nrows, ncols, nrows*ncols, size);
            MPI_Finalize();
            exit(0);
        }
    }
    else {
        nrows = ncols = (int)sqrt(size);
        dims[0] = dims[1] = 0;
    }

    /*************************************************************/
    /* create cartesian topology for processes */
    /*************************************************************/
    MPI_Dims_create(size, ndims, dims);
    if(my_rank == 0)
        printf("PW[%d], CommSz[%d]: PEdims = [%d x %d]\n",
                my_rank,     size,       dims[0], dims[1]);

    /* create cartesian mapping */
    int periods[ndims];
    periods[0] = periods[1] = 0; /* periodic shift is .false. */
    int reorder = true;
    MPI_Comm comm2D;
    int ierr = 0;
    ierr = MPI_Cart_create(MPI_COMM_WORLD, ndims, dims, periods, reorder,
                           &comm2D);
    if (ierr != 0)
        printf("ERROR[%d] creating CART\n", ierr);

    /* find my coordinates in the cartesian communicator group */
    int coord[ndims];
    MPI_Cart_coords(comm2D, my_rank, ndims, coord);

    /* use my cartesian coordinates to find my rank in cartesian group*/
    int my_cart_rank;
    MPI_Cart_rank(comm2D, coord, &my_cart_rank);

    //int source, dest;
    /* get my neighbors; axis is coordinate dimension of shift */
    /* axis=0 ==> shift along the rows: P[my_row-1]: P[me] : P[my_row+1] */
    /* axis=1 ==> shift along the columns P[my_col-1]: P[me] : P[my_col+1] */
    int nbr_i_lo, nbr_i_hi;
    MPI_Cart_shift(comm2D, dims[0], DISP, &nbr_i_lo, &nbr_i_hi);
    nbr_i_lo = wrap_row(ncols, nbr_i_lo);
    nbr_i_hi = wrap_row(ncols, nbr_i_hi);
    printf("PW[%2d] Coord(%d,%d): SHIFT_DIM[%d], Shift=%d: "
                                "nbr_lo[%2d] P[%2d] nbr_hi[%2d]\n",
            my_rank, coord[0], coord[1], SHIFT_ROW,  DISP,
                                    nbr_i_lo, my_rank,   nbr_i_hi);

    int nbr_j_lo, nbr_j_hi;
    MPI_Cart_shift(comm2D, dims[1], DISP, &nbr_j_lo, &nbr_j_hi);
    nbr_j_lo = wrap_col(nrows, nbr_j_lo);
    nbr_j_hi = wrap_col(nrows, nbr_j_hi);
    printf("PW[%2d] Coord(%d,%d): SHIFT_DIM[%d], Shift=%d: "
                                "nbr_lo[%2d] P[%2d] nbr_hi[%2d]\n",
            my_rank, coord[0], coord[1], SHIFT_COL,  DISP,
                                    nbr_j_lo, my_rank,   nbr_j_hi);
    fflush(stdout);

    MPI_Comm_free( &comm2D );
    MPI_Finalize();
    return 0;
}

int wrap_dim(int dim_width, int idx) {
    if (idx < 0)
        return dim_width + idx;
    return idx;
}
int wrap_row(int row_width, int col) {  return wrap_dim(row_width, col); }
int wrap_col(int col_height, int row) { return wrap_dim(col_height, row); }

/* cannon.c
 * --------
 * Simplified Matrix-Matrix Multiplication
 *
 *  This code is based on Cannon algorithm for matrix matrix multiplication.
 *  The main assumption in Cannon is that both A and B matrix must be square
 *  matrix and number of processors must be equal to the no of elements in
 *  A matrix.
 */
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define ndims 2 // 2 Dimension topology
#define SHIFT_ROW 1     // coord[1] is j
#define SHIFT_COL 0     // coord[0] is i

enum TaskRanks { Master = 0 };
// MxN Matrix: M rows, N columns
typedef struct MatrixSize {
  int m;    // rows    indexed by i
  int n;    // columns indexed by j
} mat_size_t;
mat_size_t get_matrices(float **L, float **R);

int main(int argc, char *argv[]) {
  // Initializing MPI
  MPI_Init(&argc, &argv);
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // Read the data only if it is the root process (rank = 0)
  int   row, column;
  float *A = NULL;
  float *B = NULL;
  if (rank == Master) {
    mat_size_t msize = get_matrices(&A, &B);
    row    = msize.m;
    column = msize.n;
  }

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Bcast(&row,    1, MPI_INT, Master, MPI_COMM_WORLD);
  MPI_Bcast(&column, 1, MPI_INT, Master, MPI_COMM_WORLD);

  // set periodicity both vertical and horizontal movement
  //    periodic == true, wraps == true
  int periods[ndims] = {1, 1};
  int dims[ndims] = {row, column};
  int reorder = 1;  // true
  // Create Cartesian mapping of processes, a topological map
  MPI_Comm cart_comm;
  MPI_Cart_create(MPI_COMM_WORLD, ndims, dims, periods, reorder, &cart_comm);

  // Sending/Assigning each A and B element to the individual processor
  //    ASSUMES 1 element per process, enough processes
  float a_ij = 0;
  MPI_Scatter(A,    1, MPI_FLOAT,
              &a_ij, 1, MPI_FLOAT,
              Master, cart_comm);
  float b_ij = 0;
  MPI_Scatter(B,    1, MPI_FLOAT,
              &b_ij, 1, MPI_FLOAT,
              Master, cart_comm);
  //printf("p[%d] a=%f, b=%f\n", rank, a_ij, b_ij);
  MPI_Barrier(MPI_COMM_WORLD);

  // 2 Dimension topology, so 2 coordinates
  int coords[2];
  // get the coordinates in the new Cartesian grid
  MPI_Cart_coords(cart_comm, rank, ndims,   coords);
  // get the new rank in Cartesian group using coords
  int cart_rank;
  MPI_Cart_rank(cart_comm, coords,  &cart_rank);
  //printf("Coordinate of processor rank %d is [%d, %d], new rank is %d\n",
  //                                 rank, coords[0], coords[1], cart_rank);

  float c_ij = 0;
  int msg_tag = 11;
  // neighbor ranks
  int right = 0, left = 0, down = 0, up = 0;
  // Pumping along systolic array:
  //    ASSUMES a square matrix
  for (int ij = 0; ij < row; ij++) {
    // get the shifted source and destination rank horizontally
    MPI_Cart_shift(cart_comm, SHIFT_ROW, ij, &right, &left);
    // get the shifted source and destination rank vertically
    MPI_Cart_shift(cart_comm, SHIFT_COL, ij, &down, &up);
    // send and receive using single buffer:
    //      shift value from RIGHT coordinate to LEFT coordinate
    MPI_Sendrecv_replace(&a_ij, 1, MPI_FLOAT,
            left,  msg_tag,     // rank of dest   (send to   left)
            right, msg_tag,     // rank of source (recv from right)
            cart_comm, MPI_STATUS_IGNORE);
    // send and receive using single buffer:
    //      shift value from DOWN coordinate to UP coordinate
    MPI_Sendrecv_replace(&b_ij, 1, MPI_FLOAT,
            up,   msg_tag,      // rank of dest   (send up)
            down, msg_tag,      // rank of source (recv from below)
            cart_comm, MPI_STATUS_IGNORE);
    // Calculation of matrix multiplication
    c_ij += a_ij * b_ij;
  }

  // allocate memory for C matrix
  float *C = (float *) calloc(sizeof(float), row * row);
  // Gather the multiplication result from every processor
  MPI_Gather(&c_ij, 1, MPI_FLOAT,
                 C, 1, MPI_FLOAT,
            Master, cart_comm);

  // Printing the result of Matrix multiplication stored in C array
  if (rank == Master) {
    int k = 0;
    printf("\nA * B:\n");
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < column; j++) {
        printf("%f\t", C[k]);
        k++;
      }
      printf("\n");
    }
  }

  MPI_Finalize();
  return 0;
}

// Assumes A and B will have same numberof rows and columns
//  TODO Should only assume that columns(A) == rows(B).
//      A_mxl . B_lxn  ==>  C_mxn
mat_size_t get_matrices(float **L, float **R) {
  int row = 0;
  int column = 0;
  // finding the number of rows & columns in A matrix
  FILE *fp;
  fp = fopen("A.txt", "r");
  int count = 0;
  char ch;
  float n;
  // scan each line
  while (fscanf(fp, "%f", &n) != -1) {
    ch = fgetc(fp);
    if (ch == '\n') {
      row++;
    }
    count++;
  }
  column = count / row;

  // Check to see to have enough processors for the elements
  int cluster_size;
  MPI_Comm_size(MPI_COMM_WORLD, &cluster_size);
  if (count != cluster_size) {
    printf("No of Processors must be equal to %d\nCode terminated\n", count);
    MPI_Finalize();
    fclose(fp);
    exit(1);
  }

  // Jump back to beginning of file for matrix A
  fseek(fp, 0, SEEK_SET);

  // allocate memory for A and B
  float *A = (float *)calloc(sizeof(float), row * column);
  float *B = (float *)calloc(sizeof(float), row * column);

  // Scanning and printing Matrix A
  int k = 0;
  printf("A matrix:\n");
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < column; j++) {
      fscanf(fp, "%f", &n);
      A[k] = n;
      printf("%f\t", A[k]);
      k++;
    }
    printf("\n");
  }
  fclose(fp);

  // Scanning and printing Matrix B
  k = 0;
  printf("\nB matrix:\n");
  // read data for B matrix
  fp = fopen("B.txt", "r");
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < column; j++) {
      fscanf(fp, "%f", &n);
      B[k] = n;
      printf("%f\t", B[k]);
      k++;
    }
    printf("\n");
  }
  fclose(fp);

  *L = A;
  *R = B;
  return (mat_size_t){row, column};
}

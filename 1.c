#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int num_processes;
    int rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("Hello world from process %d of %d", rank, num_processes);
    MPI_Finalize();
}
// // to compile with arguments
// mpicc -o 1 1.c
// // to run with arguments
// mpirun -np 4 ./1

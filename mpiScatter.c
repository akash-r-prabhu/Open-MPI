// to show how to use MPI_Scatter

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int num_processes;
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int data[4] = {1, 2, 3, 4};
    int data_received;
    MPI_Scatter(data, 1, MPI_INT, &data_received, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Process %d received data %d from process %d\n", rank, data_received, 0);
    MPI_Finalize();
    return 0;
}

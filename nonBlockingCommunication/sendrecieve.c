#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void roundRobin(int num_processes, int rank)
{
    int next = (rank + 1) % num_processes;
    int prev = (rank + num_processes - 1) % num_processes;
    MPI_Request request;
    MPI_Status status;
    int data;
    data = rank;
    if (rank == 0)
    {
        MPI_Isend(&data, 1, MPI_INT, next, 0, MPI_COMM_WORLD, &request);
        MPI_Recv(&data, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &status);
        printf("Process %d received data %d from process %d\n", rank, data, prev);
    }

    else
    {
        MPI_Recv(&data, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &status);
        printf("Process %d received data %d from process %d\n", rank, data, prev);
        MPI_Isend(&data, 1, MPI_INT, next, 0, MPI_COMM_WORLD, &request);
    }
}

int main(int argc, char **argv)
{
    int num_processes;
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    roundRobin(num_processes, rank);
    MPI_Finalize();
    return 0;
}
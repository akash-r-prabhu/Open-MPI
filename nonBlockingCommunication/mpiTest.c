// mpi test is to check if request is completed or not

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int num_processes;
    int rank;
    int flag;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int data;
    MPI_Request request;
    MPI_Status status;
    if (rank == 0)
    {
        data = 100;
        MPI_Isend(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status); // wait for request to complete
        printf("Process %d sent data %d to process %d", rank, data, 1);
    }
    if (rank == 1)
    {
        MPI_Test(&request, &flag, &status);
        if (flag)
        {
            printf("Process %d received data %d from process %d", rank, data, 0);
        }
        else
        {
            printf("Process %d did not receive data from process %d", rank, 0);
        }
    }
    else
    {
        MPI_Irecv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status); // wait for request to complete
    }
    MPI_Finalize();
    return 0;
}

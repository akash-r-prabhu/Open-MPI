#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void globalSum(int data[], int rank, int size)
{

    int recieve;
    // int localSum = 0;
    int nextData;
    MPI_Scatter(data, 1, MPI_INT, &recieve, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == size - 1)
    {
        MPI_Send(&recieve, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Recv(&nextData, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        recieve += nextData;
        if (rank != 0)
            MPI_Send(&recieve, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD);
    }
    if (rank == 0)
        printf("Sum is %d\n", recieve);
}

int main(int argc, char **argv)
{

    int rank, size;
    int data[] = {5, 2, -1, -3, 6, 5, -7, 2};
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    globalSum(data, rank, size);
    MPI_Finalize();

    return 0;
}
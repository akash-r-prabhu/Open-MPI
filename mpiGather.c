#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

// to calculate average of array
int main(int argc, char **argv)
{
    int data[1000];
    int rank, size;
    float finalAvg[1000];
    for (int i = 0; i < 1000; i++)
    {
        data[i] = i % 100;
    }
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *subarray = (int *)malloc((1000 / size) * sizeof(int));
    MPI_Scatter(data, 1000 / size, MPI_INT, subarray, 1000 / size, MPI_INT, 0, MPI_COMM_WORLD);
    printf("I am rank %d \n", rank);
    int sum = 0;
    for (int i = 0; i < 1000 / size; i++)
    {
        sum += subarray[i];
    }
    int avg = sum / (1000 / size);

    MPI_Gather(&avg, 1, MPI_INT, &finalAvg, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        int sum = 0;
        for (int i = 0; i < sizeof(finalAvg) / sizeof(int); i++)
        {
            sum += finalAvg[i];
        }
        printf("Average is %d\n", sum / size);
    }

    MPI_Finalize();
}

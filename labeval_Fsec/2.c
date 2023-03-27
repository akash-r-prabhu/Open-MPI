#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
void linearSearch(int data[], int rank, int size, int toBeFound)
{
    int recieve;
    int nextData;
    int subArraySize = 2000 / size;
    int *subArray = (int *)malloc(subArraySize * sizeof(int));
    MPI_Scatter(data, subArraySize, MPI_INT, subArray, subArraySize, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < subArraySize; i++)
    {
        if (subArray[i] == toBeFound)
        {
            printf("Found at %d\n************************************\n", rank);
            printf("And the array is ");
            for (int j = 0; j < subArraySize; j++)
            {
                printf("%d ", subArray[j]);
            }
            MPI_Abort(MPI_COMM_WORLD, 0);
            return;
        }
    }
}

int main(int argc, char **argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *data = (int *)malloc(2000 * sizeof(int));
    for (int i = 0; i < 2000; i++)
    {
        data[i] = i;
    }
    int toBeFound = data[1300];
    linearSearch(data, rank, size, toBeFound);

    MPI_Finalize();
}
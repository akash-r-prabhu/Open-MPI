#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int recv[3];
    // 2d array to store the random numbers
    int arr[][3] = {
        {10, 3, 100},
        {10, NULL, NULL},
        {10, NULL, 9},
        {2, 4, 5},
        {1, 100, 0}};

    // int arr[][5] = {
    //     {10, 10, 10, 2, 1},
    //     {3, NULL, NULL, 4, 100},
    //     {100, NULL, 9, 5, 0}};

    // print the array
    // for (int i = 0; i < 5; i++)
    // {
    //     for (int j = 0; j < 3; j++)
    //     {
    //         printf("%d ", arr[i][j]);
    //     }
    //     printf("\n");
    // }

    // scatter the array
    MPI_Scatter(arr, 3, MPI_INT, recv, 3, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        int max = recv[0];
        int maxIndex = 0;

        for (int i = 0; i < 3; i++)
        {
            if (recv[i] > max)
            {
                max = recv[i];
                maxIndex = i;
            }
        }
        printf("Maximum applications created is  %d and the application is  %d\n", max, maxIndex + 1);
    }

    MPI_Finalize();
}
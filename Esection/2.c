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

    int arr[][3] = {
        {10, 3, 100},
        {10, NULL, NULL},
        {10, NULL, 9},
        {2, 4, 5},
        {1, 100, 0}};


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
    else if (rank == 4)
    {
        int count = 0;
        for (int i = 0; i < 3; i++)
        {

            if (recv[i] != NULL)
                count++;
        }
        printf("Number of Errors is  %d\n", count);
    }
    else if (rank == 2)
    {
        int count = 0;
        for (int i = 0; i < 3; i++)
        {

            if (recv[i] != NULL)
                count++;
        }
        printf("Number of Backups  %d\n", count);
    }
    else if (rank == 3)
    {
        int sum = 0;
        for (int i = 0; i < 3; i++)
        {

            if (recv[i] != NULL)
                sum += recv[i];
        }
        printf("Total no of objects deleted  %d\n", sum);
    }

    MPI_Finalize();
}

// to run
// mpicc 2.c  
// mpirun --oversubscribe -np 5 ./a.out |sort
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int process_rank, process_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &process_size);

    // read data and store in process 0
    int dataset[3][4] = {
        {1, 10, 10, 2},
        {3, 0, 40, 0},
        {2, 100, 9, 5}};
    int final_result = 0;

    if (process_rank == 0)
    {
        // process 0 sends tasks to other processes
        MPI_Request requests[3];
        int task[3] = {1, 2, 3};
        int i = 1;
        while (i < process_size)
        {
            MPI_Isend(&task[i - 1], 1, MPI_INT, i, 0, MPI_COMM_WORLD, &requests[i - 1]);
            i++;
        }

        // process 0 receives results from other processes
        int j = 1;
        for (j = 1; j < process_size; j++)
        {
            MPI_Recv(&final_result, 1, MPI_INT, j, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (task[j - 1] == 1)
            {
                printf("Users who purchased maximum mobile phones: %d\n", final_result);
            }
            else if (task[j - 1] == 2)
            {
                printf("Total number of laptops sold: %d\n", final_result);
            }
            else if (task[j - 1] == 3)
            {
                printf("User with least number of purchases: %d\n", final_result);
            }
            else if (task[j - 1] == 4)
            {
                printf("Product least purchased: %d\n", final_result);
            }
        }
    }
    else if (process_rank == 1)
    {
        // process 1 calculates total number of laptops sold
        int sum = 0;
        int i = 0;
        while (i < 3)
        {
            sum += dataset[i][0];
            i++;
        }
        MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    else if (process_rank == 2)
    {
        // process 2 finds user with least number of purchases
        int min = dataset[0][0], user = 1;
        int i = 1;
        while (i < 3)
        {
            if (dataset[i][0] < min)
            {
                min = dataset[i][0];
                user = i + 1;
            }
            i++;
        }
        MPI_Send(&user, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    else if (process_rank == 3)
    {
        // process 3 calculates product least purchased
        int min = dataset[0][1], product = 2;
        int i = 1;
        for (i = 1; i < 4; i++)
        {
            if (dataset[0][i] < min)
            {
                min = dataset[0][i];
                product = i + 1;
            }
        }
        MPI_Send(&product, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}

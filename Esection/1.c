#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Design and implement a system using the principles of distributed computing and MPI programming.
// Simulate a board game where each process does the following:
// Generates a random number between -100 to +100.
// Each process sends its generated random number to its prev.  rank node.
// Each process - Print the rank of the process and the random number generated and to which process the random number is communicated.
// Each process - Print the number received by the process from which rank the number is received.
// When a process generates a random number between (0 and 5) communicate the number with the process 0
// Stop the game when any one process generates a value of zero or after two rounds.

int main(int argc, char **argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // loop twice
    for (int i = 0; i < 2; i++)
    {

        // create random number with current time
        srand(time(0) + rank);
        int myrand = rand();
        myrand = myrand % 201 - 100;

        // to test if 0 to 5 works uncomment below
        // myrand = 1;

        // to test game over uncomment below
        // if (rank == 2)
        // {
        //     myrand = 0;
        // }

        int prev = rank - 1;
        int next = rank + 1;
        // between 0 and 5

        if (rank == 0)
        {
            prev = size - 1;
            if (myrand > 0 && myrand < 5)
            {
                printf("Recieved number between 0 and 5 \n ");
            }
        }
        if (rank == size - 1)
        {
            next = 0;
        }
        int recv;
        MPI_Send(&myrand, 1, MPI_INT, prev, 0, MPI_COMM_WORLD);
        MPI_Recv(&recv, 1, MPI_INT, next, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("I am rank %d and my random number is %d and I sent it to %d and I received %d from %d\n", rank, myrand, prev, recv, next);
        if (myrand > 0 && myrand < 5)
        {
            MPI_Send(&myrand, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
        else if (myrand == 0)
        {
            printf("Game Over");
            MPI_Abort(MPI_COMM_WORLD, 0);
        }
    }
    MPI_Finalize();
}
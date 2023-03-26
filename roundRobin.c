#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

void roundRobin(int rank, int size)
{
    long randMine, randPrev;

    int rankNext = (rank + 1) % size;
    int rankPrev = rank == 0 ? size - 1 : rank - 1;

    // create a random number
    srand(rank);
    randMine = rand();

    // send to next process
    MPI_Send(&randMine, 1, MPI_LONG, rankNext, 0, MPI_COMM_WORLD);
    // receive from previous process
    MPI_Recv(&randPrev, 1, MPI_LONG, rankPrev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    // print received number
    printf("my rank is %d and my random number is %ld\n", rank, randMine);
    printf("Process %d received %ld from process %d\n", rank, randPrev, rankPrev);
}
int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // call round robin function
    roundRobin(rank, size);

    MPI_Finalize();
    return 0;
}
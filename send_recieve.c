#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void roundRobin(int rank, int size)
{
    int rankNext = (rank + 1) % size;
    int rankPrev = rank == 0 ? size - 1 : rank - 1;
    int tag = 0;
    MPI_Status status;
    long randMine, randPrev;
    srand(rank);
    randMine = rand();
    MPI_Sendrecv(&randMine, 1, MPI_LONG, rankNext, tag, &randPrev, 1, MPI_LONG, rankPrev, tag, MPI_COMM_WORLD, &status);
    printf("my rank is %d and my random number is %ld\n", rank, randMine);
    printf("Process %d received %ld from process %d\n", rank, randPrev, rankPrev);
}

int main(int argc, char **argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    roundRobin(rank, size);
    MPI_Finalize();
}
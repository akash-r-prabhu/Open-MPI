// program to find sum of elements of an array using MPI_Reduce
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int maint(int argc, char **argv)
{
    int rank, size;
    int data[] = {1, 2, 3, 4};

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
}
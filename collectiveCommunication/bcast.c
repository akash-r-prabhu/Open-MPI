// MPI_Bcast - one to all or broadcast
#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int num_processes;
    int rank;
    int data = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    {
        data = 100;
    }
    MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Process %d received data %d from process 0\n", rank, data);
    MPI_Finalize();
    return 0;
}

// output
// macbook@akassss collectiveCommunication % mpirun --oversubscribe -np 4 ./a.out
// Process 0 received data 100 from process 0
// Process 1 received data 100 from process 0
// Process 2 received data 100 from process 0
// Process 3 received data 100 from process 0

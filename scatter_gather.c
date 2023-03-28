#include "mpi.h"
#include <stdio.h>
#define SIZE 16
// Demonstate the storage location of data during scatter in each process
int main(int argc, char *argv[])
{
	int numtasks, rank, sendcount, recvcount, source;
	float sendbuf[SIZE] = {111.0, 20.0, 32.0, 124.0, 15.0, 6.0, 47.0, 111.0, 79.0, 170.0, 11.0, 212.0, 13.0, 114.0, 415.0, 16.0};
	int gt[4];
	float recvbuf[SIZE];
	int count = 0, final_val = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

	// if (numtasks == SIZE) {
	//  define source task and elements to send/receive, then perform collective scatter
	source = 1;
	sendcount = 4;
	recvcount = 4;
	MPI_Scatter(sendbuf, sendcount, MPI_FLOAT, recvbuf, recvcount, MPI_FLOAT, source, MPI_COMM_WORLD);

	for (int i = 0; i < 4; i++)
	{
		if (recvbuf[i] > 100.0)
			count++;
	}
	printf(" \n Rank %d Count %d ", rank, count);

	MPI_Barrier(MPI_COMM_WORLD);

	MPI_Gather(&count, 1, MPI_INT, &gt, 1, MPI_INT, 0, MPI_COMM_WORLD);

	MPI_Barrier(MPI_COMM_WORLD);

	if (rank == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			printf(" **%d ", gt[i]);
			final_val = final_val + gt[i];
		}
		printf(" rank %d  Final val %d \n ", rank, final_val);
	}

	MPI_Finalize();
}

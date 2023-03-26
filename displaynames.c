
/*
 * Display name of all the processors
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <mpi.h>
int global=0;
//#define NAMELEN 60

int main(int argc, char **argv)
{
    MPI_Status  status;
    int rank,np,length,i,left,right,tag=0,G,flag;
    char name[MPI_MAX_PROCESSOR_NAME+1];
    char string[20],string2[20];
   // char myname[NAMELEN];
    MPI_Init(&argc, &argv);    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Get_processor_name(name, &length);

    printf("\n rank : %d, hostname : %s\n ", rank,name);
	
    MPI_Finalize();
    return 0;
}

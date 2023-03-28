#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int get_random_number(int seed){
    int randNum;
    // srand(time(NULL) + seed); 
    
    randNum = rand() % 201 - 100;

    return randNum;
}

int get_next_process(int taskId, int numTasks){
    return (taskId+1)%numTasks;
}

int get_prev_process(int taskId, int numTaks){
    if (taskId == 0)
        return numTaks-1;
    else{
        return taskId-1;
    }
}

int main(int argc, char *argv[]){

    int numTasks, taskId;

    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numTasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskId);

    int prevTask = get_prev_process(taskId, numTasks), nextTask = get_next_process(taskId, numTasks);

    int round = 1, runGame = 1;

    while( runGame ){
        int myRandNum = get_random_number(taskId);
        int otherRandNum;

        MPI_Send(&myRandNum, 1, MPI_INT, prevTask, 1, MPI_COMM_WORLD);
        printf("Process %d Sending number %d to process %d\n", taskId, myRandNum, prevTask);

        MPI_Recv(&otherRandNum, 1, MPI_INT, nextTask, 1, MPI_COMM_WORLD, &status);
        printf("Process %d recived number %d from process %d\n", taskId, otherRandNum, nextTask);

        if ((myRandNum == 0 && round>2)){
            runGame = 0;
        }
        round++;
        MPI_Barrier(MPI_COMM_WORLD);
    }

    MPI_Finalize();
    
}
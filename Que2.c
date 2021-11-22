#include "mpi.h"
#include <stdio.h>

//MPI program to send integer from one process to another

//Number of processes - 2
//Non - blocking send and receive

int main(int argc, char* argv[])
{
  int rank, size;
    int tag, destination, count;
    int buffer; 

    tag = 1234;
    destination = 1; 
    count = 1; 
    MPI_Status status;
    MPI_Request request = MPI_REQUEST_NULL;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 

    if (rank == 0) 
    {
      printf("Number of processes : %d \n",size);
        buffer = 100;
        MPI_Isend(&buffer, count, MPI_INT, destination, tag, MPI_COMM_WORLD, &request); 
    }

    if (rank == destination) 
    {
        MPI_Irecv(&buffer, count, MPI_INT, 0, tag, MPI_COMM_WORLD, &request); 
    }

    MPI_Wait(&request, &status); 

    if (rank == 0) {
        printf("The number %d is sent by process %d\n", buffer,rank);
    }
    if (rank == destination) {
        printf("The number %d is received by process %d\n", buffer,rank);
    }

    MPI_Finalize();

  return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>

void  my_bcast(void* data, int count, MPI_Datatype datatype, int root, MPI_Comm communicator) {
  int world_rank;
  int world_size; 

  MPI_Comm_rank(communicator, &world_rank);
  MPI_Comm_size(communicator, &world_size);

  if (world_rank == root) {
    MPI_Send(data, count, datatype, 2 * world_rank + 1, 0, communicator);
    printf("Process %d sent to %d... Data: %s\n", world_rank, 2 * world_rank + 1, data);
    MPI_Send(data, count, datatype, 2 * world_rank + 2, 0, communicator);
    printf("Process %d sent to %d... Data: %s\n", world_rank, 2 * world_rank + 2, data);
  } else if (2 * world_rank + 2 <= world_size - 1) {
    MPI_Recv(data, count, datatype, (world_rank - 1)/2, 0, communicator, MPI_STATUS_IGNORE);
    printf("Process %d received from %d... Data: %s\n", world_rank, (world_rank - 1)/2, data);
    MPI_Send(data, count, datatype, 2 * world_rank + 1, 0, communicator);
    printf("Process %d sent to %d... Data: %s\n", world_rank, 2 * world_rank + 1, data);
    MPI_Send(data, count, datatype, 2 * world_rank + 2, 0, communicator);
    printf("Process %d sent to %d... Data: %s\n", world_rank, 2 * world_rank + 2, data);
  } else {
    MPI_Recv(data, count, datatype, (world_rank - 1)/2, 0, communicator, MPI_STATUS_IGNORE);
    printf("Process %d received from %d... Data: %s\n", world_rank, (world_rank - 1)/2, data);
  }
}

int main(int argc, char** argv) {
  int dataLength = atoi(argv[1]);
  MPI_Init(NULL, NULL);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  char data[dataLength];
  if (world_rank == 0) {
    strcpy(data, "Ana are mere.");
    my_bcast(&data, dataLength + 1, MPI_CHAR, 0, MPI_COMM_WORLD);
  } else {
    my_bcast(&data, dataLength + 1, MPI_CHAR, 0, MPI_COMM_WORLD);
  }

  MPI_Finalize();
} 

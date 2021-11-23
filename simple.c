#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>

void my_bcast(void* data, int count, MPI_Datatype datatype, int root, MPI_Comm communicator) {
  int world_rank;
  int world_size;

  MPI_Comm_rank(communicator, &world_rank);
  MPI_Comm_size(communicator, &world_size);

  if (world_rank == root) {
    int i;
    for (i = 0; i < world_size; i++) {
      if (i != world_rank) {
        MPI_Send(data, count, datatype, i, 0, communicator);
        printf("Process %d sent to %d... Data: %s\n", world_rank, i, data);
      }
    }
  } else {
    MPI_Recv(data, count, datatype, root, 0, communicator, MPI_STATUS_IGNORE);
    printf("Process %d received from %d... Data: %s\n", world_rank, root, data);
  }
}

int main(int argc, char** argv) {
  MPI_Init(NULL, NULL);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  char data[120];
  if (world_rank == 0) {
    strcpy(data, "Ana are mere.");
    my_bcast(&data, strlen(data)+1, MPI_CHAR, 0, MPI_COMM_WORLD);
  } else {
    my_bcast(&data, strlen(data)+1, MPI_CHAR, 0, MPI_COMM_WORLD);
  }

  MPI_Finalize();
}
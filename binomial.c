#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>

void my_bcast(void *data, int count, MPI_Datatype datatype, int root, MPI_Comm communicator){
    int world_rank;
    int world_size;
    int source, destination;

    MPI_Comm_rank(communicator, &world_rank);
    MPI_Comm_size(communicator, &world_size);

    int relative_rank = (world_rank >= root) ? world_rank - root : world_rank - root + world_size;
    int mask = 0x1;

    while (mask < world_size) {
        if (relative_rank & mask) {
            source = world_rank - mask;

            if (source < 0)
                source += world_size;

            MPI_Recv(data, count, datatype, source, 0, communicator, MPI_STATUS_IGNORE);
            printf("Process %d received from %d... Data: %s\n", world_rank, source, data);
            break;
        }
        mask <<= 1;
    }


    mask >>= 1;

    while (mask > 0) {
        if (relative_rank + mask < world_size) {
            destination = world_rank + mask;

            if (destination >= world_size)
                destination -= world_size;
        
            MPI_Send(data, count, datatype, destination, 0, communicator);
            printf("Process %d sent to %d... Data: %s\n", world_rank, destination, data);
        }
        mask >>= 1;
    }
}

int main(int argc, char **argv) {
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
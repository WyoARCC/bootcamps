#include <stdio.h>
#include "mpi.h"

main(int argc, char **argv){

int my_rank; // rank of process
int p;  //Number of provesses
int source; //rank of the sender
int dest; //rank of the receiver
int tag = 50; // tag for messages
char message[100];   // storage for messages
MPI_Status status;  // return status for receive

MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
MPI_Comm_size(MPI_COMM_WORLD, &p);

if (my_rank != 0) {
	sprintf(message, "Greetings form process %d",my_rank);
    dest = 0;
    MPI_Send(message, strlen(message)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
	}
	else {
		for(source = 1; source < p; source++){
			MPI_Recv(message, 100, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status);
			printf("%s\n", message);
 	     }
	}

	MPI_Finalize();
}

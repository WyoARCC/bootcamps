#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char *argv[]){

    int my_rank; // rank of process
    int p;  //Number of provesses
    int source; //rank of the sender
    int dest; //rank of the receiver
    int tag = 50; // tag for messages
    char message[100];   // storage for messages
    int thd_lvl;
    MPI_Status status;  // return status for receive
    

    MPI_Init_thread(&argc, &argv, MPI_THREAD_SINGLE, &thd_lvl);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (my_rank != 0) {
        sprintf(message, "Greetings from process %d",my_rank);
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
    return 0;
}

#include <stdio.h>
#include <mpi.h>

int main( int argc, char *argv[] ) {

	int rank;
	int nproc;
	int thd_lvl;

	MPI_Init_thread(&argc, &argv, MPI_THREAD_SINGLE,&thd_lvl);

	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	printf("Hello from process %d of %d total\n",rank,nproc);

	MPI_Finalize();

	return 0;
}

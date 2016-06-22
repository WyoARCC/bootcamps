#include <stdio.h>
#include <math.h>
#include <mpi.h>

static long steps = 1000000;

int main( int argc, char *argv[] ) { 

	int nproc,rank,thd_lvl;
	int i,isteps;

	double step;
	double x;
	double pi;
	double local_sum = 0.0;
	double sum = 0.0;

	MPI_Init_thread(&argc,&argv,MPI_THREAD_SINGLE,&thd_lvl);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	step = 1.0 / (double) steps;

	isteps = steps / nproc;
	
		
	for (i = rank*isteps; i <  (rank*isteps + isteps); i++) {
		x = (i + 0.5) * step;
	    local_sum = local_sum + 4.0 / (1.0 + x*x);
	}
	// printf("[%d] local_sum = %lf\n",rank,local_sum);
	
	MPI_Barrier(MPI_COMM_WORLD);

	// Issue MPI reduce local sums to final sum
	MPI_Reduce(&local_sum,&sum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

	// Final scaling value
	if ( 0 == rank ) {
		pi = step * sum;
		printf("The final value of calculated Pi is: %13.11lf\n",pi);
	}

	MPI_Finalize();

	return 0;

}

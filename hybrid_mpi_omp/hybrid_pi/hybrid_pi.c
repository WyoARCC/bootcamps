#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include <omp.h>

static long steps = 10000000;

void calculate_indices(int rank, int size, int *idx, int *isteps) {

	int residual = 0;
	*isteps = steps / size;

	if (rank == size-1)
		residual = steps % size;

	idx[0] = rank* (*isteps);
	idx[1] = idx[0] + (*isteps) + residual - 1;
	
	return;
}

int main( int argc, char *argv[] ) { 

	int nproc,rank;			// MPI size and rank
        int thd_req,thd_lvl;		// Thread requirement & provided
	int i,isteps;			// Looping variables.
        int idx[2] = {0,0};		// Loop start and end

	double step;			// Number of steps to take
	double x;			// Local calculation variable
	double pi;			// Final value for PI
	double local_sum = 0.0;		// Local quadrature sum
	double sum = 0.0;		// Global quadrature sum


	// Initialize MPI Environment
	thd_req = MPI_THREAD_FUNNELED;	// Thread Level required
	MPI_Init_thread(&argc,&argv,thd_req,&thd_lvl);

	// MPI Communicator Size
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);

	// MPI Local Process Rank
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	// Calculate the step size.
	step = 1.0 / (double) (steps);

	// Divide segments, and give the rank N-1 the residual extra
	calculate_indices(rank,nproc,idx,&isteps);

	printf("[%03d] indices = [%d,%d],npts = %d \n",\
		rank,idx[0],idx[1],(idx[1] - idx[0] + 1)
	);
	
	#pragma omp parallel for private(i,x) reduction(+:local_sum)
	for (i = idx[0]; i <=  idx[1]; i++) {
		x = ((double)i + 0.5) * step;
	    local_sum = local_sum + 4.0 / (1.0 + x*x);
	}

	// Print the local sum if diesired
	// printf("[%d] local_sum = %lf\n",rank,local_sum);
	
	// Create a explicit barrier -- ( Try without ;) )
	MPI_Barrier(MPI_COMM_WORLD);

	// Issue MPI reduce local sums to final sum
	MPI_Reduce(&local_sum,&sum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

	// Final scaling value & print result
	if ( 0 == rank ) {
		pi = step * sum;
		printf("The final value of calculated Pi is: %13.11lf\n",pi);
		printf("Tolerance: 100.0 * (pi - M_PI) / M_PI =  %f\n",100.0*(pi - M_PI)/M_PI);
	}

	MPI_Finalize();

	return 0;

}

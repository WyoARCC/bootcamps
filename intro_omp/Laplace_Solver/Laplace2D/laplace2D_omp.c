/* 
 * Program for a Laplace 2D solver using a Jacobi simple point iterator
 * Parallel version with OpenMP
 * Written at ARCC, University of Wyoming
 * (Compile with -fopenmp and -lm flags!)
 */

#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

// Using a square matrix of dimension SIZE*SIZE
#define SIZE 200 

int main() 
{
	// Desired tolerance for accuracy
	double tol = 1E-5;
	// Temp. variables to store error and difference
	double err = 0.0;
	double diff = 0.0;
	
	// To prevent getting stuck in an infinite loop
	int max_iter = 20000;
	int iter = 0;

	// Matrices storing previous and next values
	double **u_old;
	double **u_new;

	// Steady state boundary conditions
	const double bound_cond = 1.0;
	
	// Counter variables
	int i, j;

	// Dynamic memory allocation for two 2D matrices of given size
	printf("Allocating %d bytes for matrices. \n", sizeof(double)*(SIZE*SIZE)*2);
	u_old = (double**)malloc(SIZE*sizeof(double));
	u_new = (double**)malloc(SIZE*sizeof(double));
	// Then allocating the space for number of elements in each row i.e. columns
	for(i = 0;i < SIZE;i++)
	{
		u_old[i] = (double*)malloc(SIZE*sizeof(double));
		u_new[i] = (double*)malloc(SIZE*sizeof(double));
	}

	// Initialization of central elements to 0.0
	// (Can parallelize this nested 'for' loop used for initialization)
	for(i = 0;i < SIZE;i++)
	{
		for(j = 0;j < SIZE;j++)
		{
			u_old[i][j] = 0.0;
			u_new[i][j] = 0.0;
		}
	}

	// Initializing the outer edges i.e. boundaries to a steady state value
	for(j = 0;j < SIZE;j++)
	{
		u_old[0][j] = 1.0;
		u_old[SIZE-1][j] = 1.0;
	}
	for(i = 1;i < SIZE - 1;i++)
	{
		u_old[i][0] = 1.0;
		u_old[i][SIZE-1] = 1.0;
	}

	// This type of computation allows for a two-level parallelization due to independence of operations 
	// amongst different elements in a matrix
	printf("Starting Jacobi iterations...\n");
	do {
		// Explicit definition of i as a private variables
		// Routine parallelization of outer for loop
#pragma omp parallel for private(i) 
		for(i = 1;i < SIZE - 1;i++)
		{
			// Making the matrices shared amongst all threads
#pragma omp parallel for private(j) shared(u_new, u_old)
			for(j = 1;j < SIZE - 1;j++)
			{
				u_new[i][j] = 0.25 * (u_old[i-1][j] + u_old[i+1][j] 
						    + u_old[i][j-1] + u_old[i][j-1]);
			}
		}	

		err = 0.0;
#pragma omp parallel for private(i)
		for(i = 1;i < SIZE - 1;i++)
		{
			// Making the same definitions as previously, except err is a reduction variable
#pragma omp parallel for private(j, diff) shared(u_new, u_old) reduction(+:err)
			for(j = 1;j < SIZE - 1;j++)
			{
				diff = u_new[i][j] - u_old[i][j];
				err += fabs(diff*diff);
			}
		}
		err = sqrtf(err);

		// Update solution from old to new
		// Similar parallelization concepts as in the first nested-for loop
#pragma omp parallel for private(i)
		for(i = 1;i < SIZE - 1;i++)
		{
#pragma omp parallel for private(j) shared(u_new, u_old)
			for(j = 1;j < SIZE - 1;j++)
			{
				u_old[i][j] = u_new[i][j];
			}
		}

		// Incrementing the counter variable
		iter++;
		
		// Uncomment the following lines to print matrix after each iteration
		/*
		// Print vector after each iteration]
		printf("After iteration %5d...\n", iter);
		for(i = 0;i < SIZE;i++)
		{
			for(j = 0;j < SIZE;j++)
			{
				printf("%f ", u_old[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		*/

		// Print error after every 20 iterations to observe convergence
		if(iter % 20 == 0)
			printf("Iteration %5d, Error = %12.6e\n", iter, err);
		

	} while ((err > tol) && (iter < max_iter));

	// Print error message if maximum iterations is reached
	if(iter >= max_iter)
		printf("WARNING: Maximum iterations reached\n");

	// Printing final update to solution
	printf("Solution reached after %6d iterations with error: %12.6e \n", err, iter);

	// Freeing previously allocated memory for two 2D matrices
	for(i = SIZE - 1;i >= 0;i--)
	{
		free(u_new[i]);
		free(u_old[i]);
	}
	free(u_new);
	free(u_old);

	return 0;
}



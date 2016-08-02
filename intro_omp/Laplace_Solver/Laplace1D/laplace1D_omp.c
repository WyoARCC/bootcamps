/*
 * Program to solve Laplace 1D equation with simple point Jacobi equation
 * Parallel version with OpenMP
 * Written at ARCC, University of Wyoming
 * (Compile with -fopenmp and -lm flag!)
 */

#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <omp.h>

// Using a vector of dimension SIZE
#define SIZE 100

int main() 
{
	// Defined tolerance
	double tol = 1E-4;
	// Temp. variables to store error and difference
	double err = 0.0;
	double diff;
	
	// To prevent getting stuck in an infinite loop
	int max_iter = 20000;
	int iter = 0;

	// Vectors to store previous and next values after each iteration
	double *u_old;
	double *u_new;

	// Steady state boundary condition
	const double bound_cond = 1.0;

	// Counter variable
	int i;

	// Dynamic memory allocation for the two vectors of type double
	printf("Allocating %d bytes for vectors. \n", sizeof(double)*SIZE*2);
	u_old = (double*)malloc(SIZE*sizeof(double));
	u_new = (double*)malloc(SIZE*sizeof(double));

	// Initializing the central elements to be 0.0
	// (Can also paralleize the initialization process)
	for(i = 0;i < SIZE;i++)
	{
		u_old[i] = 0.0;
		u_new[i] = 0.0;
	}

	// Initializing boundary conditions for corner elements
	u_old[0] = bound_cond;
	u_old[SIZE-1] = bound_cond;

	printf("Starting Jacobi iterations...\n");
	do {
		// Parallelizing the 'for' loop due to independent operations
#pragma omp parallel for
		for(i = 1;i < SIZE - 1;i++)
		{
			u_new[i] = 0.5 * (u_old[i-1] + u_old[i+1]);
		}

		// Block of code to find error between consecutive iterations
		err = 0.0;
		// Similar OpenMP concept as previously
		// 'err' can be made a reduction variable because of the nature of operation
#pragma omp parallel for reduction(+:err)
		for(i = 1;i < SIZE - 1;i++)
		{
			diff = u_new[i] - u_old[i];
			err += fabs(diff*diff);
		}
		err = sqrtf(err);

		// Update solution from old to new
#pragma omp parallel for 
		for(i = 1;i < SIZE - 1;i++)
		{
			u_old[i] = u_new[i];
		}

		// Updating the counter variable
		iter++;

		// Uncomment the following code to print vectors after each iteration
		/*
		// Print vector after each iteration]
		printf("After iteration %5d...\n", iter);
		for(i = 0;i < SIZE;i++)
		{
			printf("%f ", u_old[i]);
		}
		printf("\n");

		// Print error after every 10 iterations to observe convergence
		if(iter % 10 == 0)	// Can change 10 to any number as necessary
			printf("Iteration %5d, Error = %12.6e\n", iter, err);
		*/

	} while ((err > tol) && (iter < max_iter));

	// Print error message if maximum iterations is exceeded
	if(iter >= max_iter)
		printf("WARNING: Maximum iterations reached\n");

	// Printing final update of computed solution
	printf("Solution reached after %6d iterations with error: %12.6e \n", iter, err);

	// Freeing dynamically allocated vectors
	free(u_new);
	free(u_old);

	return 0;
}



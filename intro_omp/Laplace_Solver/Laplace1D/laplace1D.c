/*
 * Program to solve Laplace 1D equation with simple point Jacobi iterative solver
 * Serial version
 * Written at ARCC, University of Wyoming. 
 * (Compile with -lm flag)
 */

#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

// Using a vector of dimension SIZE
#define SIZE 100

int main() 
{
	// Defined tolerance 
	double tol = 1E-4;
	// Temp. variables to store error and difference
	double err = 0.0;
	double diff = 0.0;
	
	// To prevent getting stuck in an infinite loop
	int max_iter = 20000;
	int iter = 0;

	// Vectors storing previous and next values
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

	// Initilaizing the central elements to be 0.0
	for(i = 0;i < SIZE;i++)
	{
		u_old[i] = 0.0;
		u_new[i] = 0.0;
	}

	// Initializing the corner elements to be steady state values
	u_old[0] = bound_cond;
	u_old[SIZE-1] = bound_cond;

	printf("Starting Jacobi iterations...\n");
	// Using a do-while loop which will ensure at least 1 iteration
	do {
		// Jacobi simple point equation for a 1D Laplace array
		for(i = 1;i < SIZE - 1;i++)
		{
			u_new[i] = 0.5 * (u_old[i-1] + u_old[i+1]);
		}

		err = 0.0;
		// Calculating the error through method of standard deviation
		for(i = 1;i < SIZE - 1;i++)
		{
			// Finding the difference in values
			diff = u_new[i] - u_old[i];
			// Adding the absolute value of difference squared to 'err'  
			err += fabs(diff*diff);
		}
		// Calculating the square root of summed quantity
		err = sqrtf(err);

		// Update solution from old to new
		for(i = 1;i < SIZE - 1;i++)
		{
			u_old[i] = u_new[i];
		}

		// Increment counter variable
		iter++;

		// Uncomment the following piece of code for debugging purposes
		// It will print the vectors after each iteration 	
		/*
		// Print vector after each iteration]
		printf("After iteration %5d...\n", iter);
		for(i = 0;i < SIZE;i++)
		{
			printf("%f ", u_old[i]);
		}
		printf("\n");
		*/

		// Print error after every 200 iterations to observe convergence
		if(iter % 200 == 0)	// Change the number 200 as necessary
			printf("Iteration %6d, Error = %12.6e\n", iter, err);

	} while ((err > tol) && (iter < max_iter)); 

	// Print error message if maximum iterations is exceeded
	if(iter >= max_iter)
		printf("WARNING: Maximum iterations reached\n");

	// Printing final update of solution 
	printf("Solution reached after %6d iterations with error: %12.6e \n", iter, err);

	// Freeing dynamically allocated vectors
	free(u_new);
	free(u_old);

	return 0;
}



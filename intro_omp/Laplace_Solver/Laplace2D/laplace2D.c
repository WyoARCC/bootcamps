/* 
 * Program for a Laplace 2D solver using a Jacobi simple point iterator
 * Serial version
 * Written at ARCC, University of Wyoming
 * (Compile with -lm flag!)
 */

#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

// Using a square matrix of dimensions SIZE*SIZE
#define SIZE 200

int main() 
{
	// Desired tolerance for accuracy
	double tol = 1E-5;
	// Temp. variables to store error and difference 
	double err = 0.0;
	double diff = 0.0;
	
	// To prevent getting stuck in an infinite loop
	int max_iter = 10000;
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
	// First allocatiing the space for number of rows
	u_old = (double**)malloc(SIZE*sizeof(double));
	u_new = (double**)malloc(SIZE*sizeof(double));
	// Then allocating the space for number of elements in each row i.e. columns
	for(i = 0;i < SIZE;i++)
	{
		u_old[i] = (double*)malloc(SIZE*sizeof(double));
		u_new[i] = (double*)malloc(SIZE*sizeof(double));
	}

	// Initialization of central elements to guess values
	for(i = 0;i < SIZE;i++)
	{
		for(j = 0;j < SIZE;j++)
		{
			u_old[i][j] = 0.0;
			u_new[i][j] = 0.0;
		}
	}

	// Setting boundary elements to steady state values
	for(j = 0;j < SIZE;j++)
	{
		u_old[0][j] = bound_cond;
		u_old[SIZE-1][j] = bound_cond;
	}
	for(i = 1;i < SIZE - 1;i++)
	{
		u_old[i][0] = bound_cond;
		u_old[i][SIZE-1] = bound_cond;
	}

	printf("Starting Jacobi iterations...\n");
	do {
		// Cycling though all central elements of 2D matrix
		for(i = 1;i < SIZE - 1;i++)
		{
			for(j = 1;j < SIZE - 1;j++)
			{
				// Using Jacobi's method for two variable functions
				u_new[i][j] = 0.25 * (u_old[i-1][j] + u_old[i+1][j] 
						    + u_old[i][j-1] + u_old[i][j-1]);
			}
		}	

		// Calculating difference between consecutive iterations
		err = 0.0;
		for(i = 1;i < SIZE - 1;i++)
		{
			for(j = 1;j < SIZE - 1;j++)
			{
				diff = u_new[i][j] - u_old[i][j];
				err += fabs(diff*diff);
			}
		}
		err = sqrtf(err);

		// Update solution from old to new
		for(i = 1;i < SIZE - 1;i++)
		{
			for(j = 1;j < SIZE - 1;j++)
			{
				u_old[i][j] = u_new[i][j];
			}
		}

		// Increment iteration counter variable
		iter++;

		// Uncomment following code to print matrix after each iteration
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
		if(iter % 20 == 0)	// Can change 20 to any number as necessary
			printf("Iteration %5d, Error = %12.6e\n", iter, err);
		

	} while ((err > tol) && (iter < max_iter));

	// Print error message if maximum iterations is reached
	if(iter >= max_iter)
		printf("WARNING: Maximum iterations reached\n");

	// Printing final update of solution
	printf("Solution reached after %6d iterations with error: %12.6e \n", err, iter);

	// Freeing memory for dynamically allocated 2D matrices (opposite of allocating)
	for(i = SIZE - 1;i >= 0;i--)
	{
		free(u_new[i]);
		free(u_old[i]);
	}
	free(u_new);
	free(u_old);

	return 0;
}



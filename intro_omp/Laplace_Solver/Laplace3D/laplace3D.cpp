/* 
 * Program for a Laplace 3D solver using a Jacobi simple point iterator
 * Serial version
 * Written at ARCC, University of Wyoming
 * (To be compiled with: 
 * g++ laplace3D.cpp -o laplace3D)
 */

#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

// Using a 3D matrix of dimensions SIZE*SIZE*SIZE
#define SIZE 75

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

	// 3D matrices storing previous and next values
	double ***u_old;
	double ***u_new;

	// Steady state boundary conditions
	const double bound_cond = 1.0;

	// Defining a multipler for better accuracy, instead of type-casting
	const double multiplier = 1.0/6.0;

	// Counter variables
	int i, j, k;

	// Dynamic memory allocation for two 3D matrices of given size
	printf("Allocating %d bytes for matrices. \n", sizeof(double)*(SIZE*SIZE*SIZE)*2);
	// First allocatiing the space for 'height (y)' of 3D array
	u_old = new double**[SIZE];
	u_new = new double**[SIZE];
	// Then allocating the space for 'width (x)' inside each 'height'ed row
	for(i = 0;i < SIZE;i++)
	{
		u_old[i] = new double*[SIZE];
		u_new[i] = new double*[SIZE];
		// Final allocation of 'depth (z)' for each element of 'height' and 'width'
		for(j = 0;j < SIZE;j++)
		{
			u_old[i][j] = new double[SIZE];
			u_new[i][j] = new double[SIZE];
		}
	}

	// Initialization of central/interior elements to guess values
	for(i = 0;i < SIZE;i++)
	{
		for(j = 0;j < SIZE;j++)
		{
			for(k = 0;k < SIZE;k++)
			{
				// (chosen 0.0 for simplicity)
				u_old[i][j][k] = 0.0;
				u_new[i][j][k] = 0.0;
			}
		}
	}

	// Setting the six faces of the 3D structure to boundary values
	for(j = 0;j < SIZE;j++)
	{
		for(k = 0;k < SIZE;k++)
		{
			u_old[0][j][k] = bound_cond;
			u_old[SIZE-1][j][k] = bound_cond;
		}
	}
	for(i = 0;i < SIZE;i++)
	{
		for(k = 0;k < SIZE;k++)
		{
			u_old[i][0][k] = bound_cond;
			u_old[i][SIZE-1][k] = bound_cond;
		}
	}
	for(i = 0;i < SIZE;i++)
	{
		for(j = 0;j < SIZE;j++)
		{
			u_old[i][j][0] = bound_cond;
			u_old[i][j][SIZE-1] = bound_cond;
		}
	}

	printf("Starting Jacobi iterations...\n");
	do {
		// Cycling though all central elements of 3D matrix
		for(i = 1;i < SIZE - 1;i++)
		{
			for(j = 1;j < SIZE - 1;j++)
			{
				for(k = 1;k < SIZE - 1;k++)
				{
					// Using Jacobi's method for 3 variable functions
					u_new[i][j][k] = multiplier * (u_old[i-1][j][k] + u_old[i+1][j][k] 
	       							             + u_old[i][j-1][k] + u_old[i][j-1][k]
											     + u_old[i][j][k-1] + u_old[i][j][k+1]);	
				}
			}
		}	

		// Calculating difference between consecutive iterations
		err = 0.0;
		for(i = 1;i < SIZE - 1;i++)
		{
			for(j = 1;j < SIZE - 1;j++)
			{
				for(k = 1;k < SIZE - 1;k++)
				{
					diff = u_new[i][j][k] - u_old[i][j][k];
					err += fabs(diff*diff);
				}
			}
		}
		err = sqrtf(err);

		// Update solution from old to new
		for(i = 1;i < SIZE - 1;i++)
		{
			for(j = 1;j < SIZE - 1;j++)
			{
				for(k = 1;k < SIZE - 1;k++)
				{
					u_old[i][j][k] = u_new[i][j][k];
				}
			}
		}

		// Increment counter variable
		iter++;

		// Uncomment following code to print the error after every 20 iterations
		/*
		if(iter % 2 == 0)	// Can change this numebr as necessary to suit the application
			printf("Iteration %5d, Error = %12.6e\n", iter, err);
		*/		
		
	} while ((err > tol) && (iter < max_iter));

	// Print error message if maximum iterations is reached
	if(iter >= max_iter)
		printf("WARNING: Maximum iterations reached\n");

	// Printing final update of solution
	printf("Solution reached after %6d iterations with error: %12.6e \n", err, iter);


	// Freeing memory for dynamically allocated 3D matrices (opposite of allocating)
	for(i = SIZE - 1;i >= 0;i--)
	{
		for(j = SIZE - 1;j >= 0;j--)
		{
			delete[] u_old[i][j];
			delete[] u_new[i][j];
		}
		delete[] u_old[i];
		delete[] u_new[i];
	}
	delete[] u_old;
	delete[] u_new;

	return 0;
}



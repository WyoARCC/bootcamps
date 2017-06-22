#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Defining a maximum number of iterations 
#define MAX_ITER 2000
// Size of sample space i.e. 100x100
#define SIZE 100

// Steady state boundary value
#define BOUND_VAL 1.0
// Initial guess to be populated everywhere else
#define INITIAL_VAL 0.0

// Define a tolerance based on requirements
#define TOL 1E-4

int main() {

	// Initiallizing two square matrices to model the heat mesh
	double **T;
	double **Ts;

	int i, j;

	// Dynamic memory allocation for two 2D matrices of given size
	printf("Allocating %ld bytes for matrices... \n",sizeof(double)*(SIZE*SIZE)*2);
	
	//First allocating the space for number of rows
	T = (double**)malloc(SIZE*sizeof(double));
	Ts = (double**)malloc(SIZE*sizeof(double));
	// Allocating the space for number of elements in each row i.e. columns
	for(i=0; i<SIZE; i++)
	{
		T[i] = (double*)malloc(SIZE*sizeof(double));
		Ts[i] = (double*)malloc(SIZE*sizeof(double));
	}
	printf("Done.\n");

	// Populating the matrices which will simulate the mesh
	for(i=0; i<SIZE; i++)
	{
		for(j=0; j<SIZE; j++)
		{
			T[i][j] = INITIAL_VAL;
			Ts[i][j] = INITIAL_VAL;
		}
	}

	for(i=0; i<SIZE; i++)
	{
		T[i][0] = Ts[i][0] = BOUND_VAL;
		T[i][SIZE-1] = Ts[i][SIZE-1] = BOUND_VAL;
		T[0][i] = Ts[0][i] = BOUND_VAL;
		T[SIZE-1][i] = Ts[SIZE-1][i] = BOUND_VAL;
	}

	int iter = 0;
	double err;
	printf("Starting Jacobi iterations...\n");
	// Starting the iterations to propagate towards steady state
	while(iter<MAX_ITER) 
	{
		do
		{
			// INSERT CODE HERE
			
			
		
			 
		}while(err>TOL);
		// Break out of loop after reaching tolerance limits
		break;
	}
	printf("Number of iterations: %d with error: %f\n",iter,err);
	
	if(iter>=MAX_ITER)
		printf("WARNING: Maximum iterations reached\n");

	// Writing data values into a text file for plotting
	FILE *f = fopen("TempEq.txt","w+");
	for(i=0;i<SIZE;i++)
	{
		for(j=0;j<SIZE;j++)
		{
			fprintf(f,"%.6f ",Ts[i][j]);
		}
		fprintf(f,"\n");
	}
	fclose(f);

	// Deallocating memory from the dynamic arrays
	printf("Deallocating memory from matrices... \n");
	for(i=SIZE-1; i>=0; i--)
	{
		free(T[i]);
		free(Ts[i]);
	}
	free(T);
	free(Ts);
	printf("Done\n");

	return 0;
}

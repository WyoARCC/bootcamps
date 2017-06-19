#include <stdio.h>
#include <math.h>

// Defining a maximum number of iterations 
#define MAX_ITER 200
// Size of sample space i.e. 10x10
#define SIZE 10 

// Steady state boundary value
#define BOUND_VAL 1.0
// Initial guess to be populated everywhere else
#define INITIAL_VAL 0.0

// Define a tolerance based on requirements
#define TOL 1e-4

int main() {

	// Initiallizing two square matrices to model the heat mesh
	float T[SIZE][SIZE];
	float Ts[SIZE][SIZE];

	int i, j;

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
	float err;
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
	printf("Number of iterations required to reach convergence: %d\n",iter);
	
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

	return 0;
}

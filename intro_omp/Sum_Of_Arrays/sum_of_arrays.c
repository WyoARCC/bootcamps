/* 
 * Code written in C with OpenMP directives to compute the sum of two arrays. 
 * This will be done in both a sequential and parallel manner and the timings compared. 
 * To be used in ARCC Bootcamp at the University of Wyoming. 
 */
 
#include <stdio.h>
#include <omp.h>

/*
 * SIZE is an integer that will decide the number of elements in the array. 
 * We want a number that is big enough for us to see the advantage of parallelism since the time taken to spawn the threads 
 * may exceed the iterations of the execution.
 */
#define SIZE 50000 

int main() 
{
	// Defining two arrays to store SIZE number of integers
	int A[SIZE];
	int B[SIZE];

	// Definfing a third array which will store the element-wise sum of A & B
	int seq_sum[SIZE];
	int par_sum[SIZE];

	// Counter variable in 'for' loop
	int i;
	
	for(i = 0;i < SIZE;i++)
	{
		// Making each element in A = 1 and each element in B = 2
		A[i] = 1;
		B[i] = 2;
	}

	// Creating a double type variable to store the starting time 
	// Calling an OpenMP function which will return the current time
	double t_start = omp_get_wtime();
	// Sequential sum
	for(i = 0;i < SIZE;i++)
	{
		// Simple addition of two elements and storing it in 'sum'
		seq_sum[i] = A[i] + B[i];
	}
	// Creating a double type variable to store the finish time of computation
	double t_end = omp_get_wtime();

	printf("Total time taken for sequential sum of %d elements: %f s\n", SIZE, (t_end - t_start));

	// Similarly for parallel execution
	t_start = omp_get_wtime();
// This statement will tell the compiler to split the iterations evenly amongst the number of threads
#pragma omp parallel for
	for(i = 0;i < SIZE;i++)
	{
		par_sum[i] = A[i] + B[i];
	}
	// Creating a double type variable to store the finish time of computation
	t_end = omp_get_wtime();

	printf("Total time taken for parallel sum of %d elements: %f s\n", SIZE, (t_end - t_start));

	return 0;
}

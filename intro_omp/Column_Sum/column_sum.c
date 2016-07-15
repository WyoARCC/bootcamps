/*
 * This is C code to find the sum of elements in a column of a 2D matrix using OpenMP.
 * Concepts such as private and shared variables along with reduction clauses will be introduced. 
 * ARCC Bootcamps, University of Wyoming
 *
 */

#include <stdio.h>
#include <stdlib.h>

//Will be using this library to provide the current time as a seed to our random number generator
#include <time.h>

#include <omp.h>

//Operating with a square matrix for simplicity
#define ROWS 10 
#define COLS 10

int main() {
	// We first need to seed our random number generator to get a truly random sequence. 
	// By providing the current time we ensure that we can get close to total randomness. 
	srand(time(NULL));

	// Defining an empty 2D matrix of dimensions ROWS*COLS
	float matrix[ROWS][COLS];

	int i, j;  // Counter variable

	// These two nested-for loops will fill the matrix will random decimal values between 0 and 1
	for(i = 0;i < ROWS;i++)  // Will traverse down the matrix 
	{
		for(j = 0;j < COLS;j++)  // Will traverse across the above row
		{
			//We also have to tell the compiler to store it as a float instead of an integer
			matrix[i][j] = (float)rand()/RAND_MAX;
			// printf("%f\t", matrix[i][j]);
		}
		// printf("\n");
	}
	
	// Defining a solution 1D array which will store the sum of all elements in a column
	float column_sum[COLS];

	// A temp variable which will store the sum of elements in each column of 'matrix'
	float sum = 0.0;
	
// By default all variables defined outside a parallel region are shared amongst all threads. 
// Making 'j' a private variable will ensure that each thread gets its own value.
#pragma omp parallel private(j)
	for(j = 0;j < COLS;j++)	 // Traverse across the matrix
	{
// The 'reduction' clause takes in the operator and the variable it is operating on. 
#pragma omp parallel for reduction(+:sum)
		for(i = 0;i < ROWS;i++)  // Traverse down the above column
		{
			// C syntax for sum = sum + matrix[i][j]
			sum += matrix[i][j];	
		}
		column_sum[j] = sum;	// Assigning the final value to column_sum
		sum = 0.0;	// Need to ensure that the sum is reset to 0
	}
	
	// Printing out the elements of column_sum
	printf("The solution vector is: \n");
	for(j = 0;j < COLS;j++)
	{
		printf("%f\t", column_sum[j]);
	}
	printf("\n");

	return 0;
}

/* 
 * Code to find the matrix-vector product using OpenMP directives. 
 * To be used at the ARCC Bootcamp at the University of Wyoming. 
 */

#include <stdio.h>
#include <stdlib.h> 

#include <omp.h>

// Can be changed to notice difference in answers
#define ROWS 5
#define COLS 5

int main() {
	// Defining a 2D matrix with known dimensions. 
	int matrix[ROWS][COLS];

	// Defining a 1D vector of suitable length for multiplication i.e. COLS*1
	int vec[COLS];  

	// Counter variables to traverse through rows and columns
	int i, j; 

	// Initializing the array to store the resultant product of size ROWS*1 
	int prod[ROWS];

	// Loops to make every element of the 2D matrix to 1
	for(i = 0;i < ROWS;i++)
	{
		for(j = 0;j < COLS;j++)
		{
			matrix[i][j] = 1;
		}
	}

	// Loop to make every element of 1D vector to 1
	for(j = 0;j < COLS;j++)
	{
		vec[j] = 1;
	}

// By default all variables outside a parallel region are shared amongst all threads 
// Making 'i' a private variable will ensure that each thread gets its own value
#pragma omp parallel private(i)
	for(i = 0;i < ROWS;i++)
	{
		int temp_sum = 0;
// The 'reduction' clause takes in the operator and the variable it is operating on 
#pragma omp parallel for reduction(+:temp_sum)
		for(j = 0;j < COLS;j++)
		{
			// Computing the temp_sum to be stored in prod 
			 temp_sum += matrix[i][j] * vec[j];
		}
		// Storing it in prod array
		prod[i] = temp_sum;
	}

	// Printing out the elements of the prod array
	printf("The product array is: \n");
	for(i = 0;i < ROWS;i++)
	{
		printf("%d\t", prod[i]);
	}
	printf("\n");

	return 0;
}




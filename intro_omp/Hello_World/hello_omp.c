/* 
 * Basic OpenMP program to print "Hello World" from each thread. 
 * Code to be used for ARCC Bootcamp at the Univresity of Wyoming. 
 */
 
#include <stdio.h>
// Need to include this header file since we are using the omp directives 
#include <omp.h>

// Regular C syntax as found in other programs
int main(int argc, char* argv[]) {
	 // Signifying that the following block of code needs to be executed in parallel.
  	 // Using '#' to denote to the compiler that we are using a directive.
#pragma omp parallel	// By doing this we have launched a certain number of threads that will execute simultaneously.  
	{
		printf("Hello World! I'm thread %d out of %d total threads.\n", 
				omp_get_thread_num(), 
				omp_get_num_threads());
	}

	return 0;
}

/*
 * omp_get_thread_num() is a function call under <omp.h> which will return a number that is unique to each thread. 
 * For example, if there are 4 threads then these threads will have numbers between 0 and 3. 
 * omp_get_num_threads() will return the total number of threads that has been assigned. 
 */

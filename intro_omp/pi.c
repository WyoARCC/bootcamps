#include <stdio.h>
#include <stdlib.h>

#include <omp.h>

// The number of segments to integrate with
static long steps = 10000000;

int main() {

	int nthd = omp_get_num_threads();
	int thd_id;

	// Calculation variables;
	int i;
	double step;
	double x;
	double pi = 0.0;
	double sum = 0.0; // Make sure to initialize the sum to 0.0

	double t0,t1;
	// Define the step size for the integration
	step = 1.0 / (double) steps;

	// Iteration
	t0 = omp_get_wtime();
#pragma omp parallel private(i,x)
	{
	thd_id = omp_get_thread_num();
#pragma omp for reduction(+:sum)
	for (i=0; i<steps; i=i+1) {
		x = (i + 0.5) * step;
		sum = sum + 4.0 / (1.0 + x*x);
	}
	}
	// Final Scaling
	pi = step * sum;
	t1 = omp_get_wtime();

	// Result
	printf("The calculated value of pi is: %13.11lf (%lf s)\n",pi,t1-t0);

	return 0;

}

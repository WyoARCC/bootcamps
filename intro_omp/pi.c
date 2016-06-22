#include <stdio.h>

// The number of segments to integrate with
static long steps = 1000;

int main() {

	// Calculation variables;
	int i;
	double step;
	double x;
	double pi;
	double sum = 0.0; // Make sure to initialize the sum to 0.0

	// Define the step size for the integration
	step = 1.0 / (double) steps;

	// Iteration
	for (i=0; i<steps; i++) {
		x = (i + 0.5) * step;
		sum = sum + 4.0 / (1.0 + x*x);
	}
	// Final Scaling
	pi = step * sum;

	// Result
	printf("The calculated value of pi is: %13.11lf\n",pi);

	return 0;
}

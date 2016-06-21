#include <stdio.h>
#include <omp.h>

int main(int argc, char* argv[]) {

#pragma omp parallel
	{
		printf("Hello World! I’m thread %d out of %d total threads.\n",
			omp_get_thread_num(),
			omp_get_num_threads()
		);
	}

	return 0;
}


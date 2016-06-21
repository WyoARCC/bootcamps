#include <stdio.h>

int square(int arg){
	return arg*arg;
}

int main() {

	int A[10] = {1,2,3,4,5,6,7,8,9,10};
	int B[10];
	int i;
	for (i=0; i<10; i++){
		B[i] = square(A[i]);
		printf("A[%d] = %04d, B[%d] = %04d\n",i,A[i],i,B[i]);
	}

	printf("A = [");
	for (i=0; i<9; i++)
		printf("%d,",A[i]);
	printf("%d]\n",A[9]);

	printf("B = [");
	for (i=0; i<9; i++)
		printf("%d,",B[i]);
	printf("%d]\n",B[9]);

	return 0;
}

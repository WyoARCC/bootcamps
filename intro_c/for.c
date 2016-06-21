#include <stdio.h>

int main() {

	int i;

	for (i=0; i<10;i++){
		printf("The value of i is %d\n",i);
		if (8 == i) printf("*** surprise: i^2 = %d ***\n",i*i);
	}

	return 0;
}

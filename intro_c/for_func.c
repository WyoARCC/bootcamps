#include <stdio.h>

int square(int arg){
	return arg*arg;
}

int main() {

	int i;

	for (i=0; i<10;i++){
		printf("The value of i is %d and it's square is %d\n",i,square(i));
	}

	return 0;
}

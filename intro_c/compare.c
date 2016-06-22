#include <stdio.h>

void compare(int a, int b) {

	if (a > b) 
		printf("%d is greater than %d\n",a,b);
	else if (a < b)
		printf("%d is less than %d\n",a,b);
	else 
		printf("%d is equal to %d\n",a,b);
}

int main() {
	
	compare(4,2);
	compare(4,5);
	compare(4,4);
	
	return 0;
}

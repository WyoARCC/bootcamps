#include <stdio.h>

int main() {
	// This is a single line comment
	printf("\n\n");

	// integers
	int integer = 5;
	printf("An integer: %d\n\n",integer);


	// floating point
	float floating = 2.3456;
	printf("A floating point: %f\n\n",floating);

	// double precision floating point
	double doubleprec = 2.345654321234;
	printf("A double precision number: %15.17lf\n\n",doubleprec);

	// characters
	char character = 's';
	printf("A character: %c\n\n",character);

	// Strings (character arrays)
	char * string = "We are have a great bootcamp!\n";
	printf("A string: %s\n\n",string);

	return 0;
}

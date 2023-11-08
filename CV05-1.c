#include <stdio.h>
#include <stdbool.h> // Od verze C23 by se nemělo používat

int main(void)
	{
	// Velikost - (sizeof vrací velikost v bitech)

	// Bool
	printf("Size of _Bool: %zu byte\n\n", sizeof(bool));


	// Char
	printf("Size of char: %zu byte\n", sizeof(char));
	printf("Size of signed char: %zu byte\n", sizeof(signed char)); 
	printf("Size of unsigned char: %zu byte\n\n", sizeof(unsigned char));

	// Int (unsigned - bez znaménka)
	printf("Size of short int: %zu byte\n", sizeof(short int)); 
	printf("Size of unsigned short int: %zu byte\n\n", sizeof(unsigned short int));
	
	printf("Size of int: %zu byte\n", sizeof(int)); 
	printf("Size of unsigned int: %zu byte\n", sizeof(unsigned int));


	printf("Size of unsigned long int: %zu byte\n", sizeof(unsigned long int)); 
	printf("Size of long int: %zu byte\n", sizeof(long int));


	printf("Size of long long int: %zu byte\n", sizeof(long long int)); 
	printf("Size of long long int: %zu byte\n", sizeof(unsigned long long int));


	printf("Size of float: %zu byte\n", sizeof(float)); 
	printf("Size of double: %zu byte\n", sizeof(double));
	printf("Size of long double: %zu byte\n", sizeof(long double));


	return 0;
	
	}
#include <stdio.h>

void swap_numbers(int *aPtr1, int *aPtr2);

int main(void)
{
	int x = 10;
	int y = 20;

	printf("Pred vymenou x=%d, y=%d\n", x ,y);

	swap_numbers(&x, &y); // Funkci je nutno předat adresy proměnných

	printf("Po vymene x=%d, y=%d", x, y);

	return 0;
}

void swap_numbers(int* aPtr1, int* aPtr2)
{
	int tmp = *aPtr1;
	*aPtr1 = *aPtr2;
	*aPtr2 = tmp;
}



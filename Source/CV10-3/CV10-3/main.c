#include <stdio.h>

void swap_numbers(int* aPtr1, int* aPtr2);
void print_numbers(int* aPtr1, int* aPtr2);

int main(void)
{
	int x = 10;
	int y = 20;

	void (*ptr_func)(int* aPtr1, int* aPtr2) = NULL; // Lokální proměnná typu ukazatel na funkci, která má dva formální parametry

	
	/*ptr_func = swap_numbers; // ptr_func = &swap_numbers

	//	printf("Pred vymenou x=%d, y=%d\n", x, y);
	//swap_numbers(&x, &y); // Funkci je nutno předat adresy proměnných
	
	print_numbers(&x, &y);


	ptr_func = print_numbers;
	ptr_func(&x, &y);

	// printf("Po vymenou x=%d, y=%d", x, y);*/

	/*! V tomto případě lze do ukazatele vložit funkci, protože mají stejnou hlavičku*/
	printf("Pred vymenou: ");
	ptr_func = print_numbers;
	ptr_func(&x, &y); // Volá se print_numbers()

	ptr_func = swap_numbers;
	ptr_func(&x, &y); // Volá se swap_numbers

	printf("Po vymene: ");
	ptr_func = print_numbers;
	ptr_func(&x, &y); // Volá se print_numbers()


	return 0;
}

void swap_numbers(int* aPtr1, int* aPtr2) // v této funkci je aPtr1 a aPtr2 lokální proměnná funkce
{
	int tmp = *aPtr1;
	*aPtr1 = *aPtr2;
	*aPtr2 = tmp;
}

void print_numbers(int* aPtr1, int* aPtr2)
{
	printf("x=%d y=%d", *aPtr1, *aPtr2);
}


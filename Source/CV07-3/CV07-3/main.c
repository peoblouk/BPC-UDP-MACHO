#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

// Kontrola prestupneho roku ve funkci
static inline bool is_leap_year(unsigned aYear)
{
	return (aYear % 400 == 0 || (aYear % 4 == 0 && aYear % 100 != 0));
}

int main(void)
{
	printf("Zadej rok: ");
	unsigned rok;
	if (scanf("%u", &rok) != 1)
	{
		printf("Chybne zadany rok!\n");
		return 1;
	}

	if (is_leap_year(rok))
		printf("Rok %u je prestupny.\n", rok);
	else
		printf("Rok %u je neprestupny. \n", rok);
	return 0;
}
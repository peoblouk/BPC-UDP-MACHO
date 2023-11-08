#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int main(void)
{
	while (1) 
	{
		unsigned rok;
		printf("Tento program urci zda je rok prestupny nebo ne\n\n");

		printf("Zadejte rok: ");
		if (scanf("%u", &rok) != 1)
		{
			printf("Chyba cteni roku\n");
			return 1;
		}

		if (rok % 4 == 0) // Ano
		{

			if (rok % 100 == 0) // Ano
			{

				if (rok % 400 == 0) // Ano
				{
					printf("Prestupny\n");
				}
				else // Ne
				{
					printf("Neprestupny\n");
				}
			}

			else // Ne
			{
				printf("Prestupny\n");
			}
		}
		else // Ne
		{
			printf("Neprestupny\n");
		}
		printf("\n");
	}
	return 0;
}
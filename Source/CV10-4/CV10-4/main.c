#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define N 10 // max velikost pole

int minmax(size_t aNum, double aData[aNum], double* aPtrmin, double* aPtrmax);

int main(void)
{
	double data[N] = {0};

	printf("Zadej pocet cisel: \n");
	size_t data_num = 0; // Proměnná pro uložení 

	if (scanf("%zu", &data_num) != 1) // Kontrola uživatel musí zadat počet prvků pole 
	{
		printf("Chyba - nebylo zadano cislo! \n");
		return 1;
	}
	
	if (data_num > N) // Kontrola
	{
		printf("Hodnota je vetší než N");
		return 2;
	}

	printf("Zadej %zu cisel:", data_num);
	for (size_t i = 0; i < data_num; i++) {
		if (scanf("%lf", &data[i]) != 1) // Čtení pole od uživatele
		{
			return 3;
		}
	}

	printf("\nElementy pole:\n");
	for (size_t i = 0; i < data_num; i++) // Kontrola čtení
	{
		printf("%lf ", data[i]);
	}
	putchar('\n'); //vytiskne jeden znak pouze lehčí forma tiskne na řádek


	double min, max; // pomocné proměnné
	if (minmax(data_num, data, &min, &max) < 0)
	{
		return 4;
	}

	printf("\nmin=%lf max=%lf\n", min, max);

	return 0;
}

int minmax(size_t aNum, double aData[aNum], double* aPtrmin, double* aPtrmax) // Funkce pro hledání minima a maxima
{
	if (aData == NULL || aPtrmin == NULL || aPtrmax == NULL || aNum == 0) // Kontrola
	{
		return -1;
	}
	*aPtrmin = *aPtrmax = aData[0]; // zpracovani prvniho prvku

	for (size_t i = 0; i < aNum; i++) // vyhledávání min a max
	{
		if (aData[i] > *aPtrmax)
			*aPtrmax = aData[i];
		else if (aData[i] < *aPtrmin)
			*aPtrmin = aData[i];
	}
	return 1;
}


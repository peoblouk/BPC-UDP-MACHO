#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // pro funkce malloc(), free()
#include "check.h" // 

/* Dynamické alokování */

int minmax(size_t aNum, double aData[aNum], double* aPtrmin, double* aPtrmax);

int main(void)
{
	double* ptr_data = NULL; // Proměnné pole 

	size_t data_num = 0; // Proměnná pro uložení 
	printf("Zadej pocet cisel:");
	if (scanf("%zu", &data_num) != 1) // Kontrola uživatel musí zadat počet prvků pole 
	{
		printf("Chyba - nebylo zadano cislo! \n");
		return 1;
	}

	ptr_data = malloc(data_num * sizeof(double)); // Alokace pole pomocí 
	if (ptr_data == NULL) // Oveření zda opravdu místo bylo alokováno
	{
		printf("Chyba alokace!");
		return 2;
	}

	printf("Zadej %zu cisel:", data_num);
	for (size_t i = 0; i < data_num; i++) {
		if (scanf("%lf", &ptr_data[i]) != 1) // Čtení pole od uživatele
		{
			free(ptr_data); // Ukončení alokace, má smysl uvolnit jen paměť, která alokována
			return 3;
		}
	}

	printf("\nElementy pole:\n");
	for (size_t i = 0; i < data_num; i++) // Kontrola čtení
	{
		printf("%lf ", ptr_data[i]);
	}
	putchar('\n'); //vytiskne jeden znak pouze lehčí forma tiskne na řádek


	double min, max; // pomocné proměnné
	if (minmax(data_num, ptr_data, &min, &max) < 0)
	{
		return 4;
	}

	printf("\nmin=%lf max=%lf\n", min, max);

	free(ptr_data); // Uvolnění paměti po alokaci (dává když nebude třeba nebo ukončením programu)

	return 0;
}

int minmax(size_t aNum, double aData[aNum], double* aPtrmin, double* aPtrmax) // Funkce pro hledání minima a maxima
{
	if (aData == NULL || aPtrmin == NULL || aPtrmax == NULL || aNum == 0) // Kontrola
	{
		return -1;
	}
	*aPtrmin = *aPtrmax = aData[0]; // zpracovani prvniho prvku

	for (size_t i = 0; i < aNum; i++) // vyhledávání min a max (algoritmus)
	{
		if (aData[i] > *aPtrmax)
			*aPtrmax = aData[i];
		else if (aData[i] < *aPtrmin)
			*aPtrmin = aData[i];
	}
	return 1;
}


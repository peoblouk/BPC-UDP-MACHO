#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // pro funkce malloc(), free()
#include "check.h"// kontrola po alokaci 

struct TData { size_t iPocet; unsigned *iData; };

int Cetnost(struct TData aData, unsigned aVysl[]);

int main(void)
{
	char FileName[256];

	printf("Zadejte jmeno souboru: ");
	if (scanf("%s", FileName) != 1)
	{
		return -1;
	}

	struct TData data = {0, NULL};

	FILE* fr = fopen(FileName, "r"); // otevøu soubor z pole
	if (fr == NULL) // oveøení zda se otevøelo 
	{
		fprintf(stderr, "Nelze otevrit vstupni soubor!");
		return 1;
	}

	if (fscanf(fr, "%zu", &data.iPocet) != 1) // Ètení poètu dat (na prvním øádku souboru vstup.txt je èíslo, které udává poèet)
	{
		fprintf(stderr, "Chyba cteni ze vstupniho souboru!");
		return 2;
	}

	data.iData = malloc(data.iPocet * sizeof(unsigned));
	
	if (data.iData == NULL)
	{
		return 3;
	}

	for (size_t i = 0; i < data.iPocet; i++)
	{
		if (fscanf(fr, "%u", &data.iData[i]) != 1) // Ètení poètu dat (na prvním øádku souboru vstup.txt je èíslo, které udává poèet)
		{
			fprintf(stderr, "Chyba cteni ze vstupniho souboru!");
			fclose(fr);
			free(data.iData);
			return 2;
		}
		// printf("|%u|", data.iData[i]);
	}
	fclose(fr);

	unsigned vysl[10] = { 0 }; //! Pozor si dát musím inicializovat na 0

	if (Cetnost(data, &vysl) < 0)
	{
		return 4;
	}

	for (size_t i = 0; i < 10; i++) {
	
		printf("%zu : %ux\n", i, vysl[i]);
	}

	free(data.iData);

	return 0;
}

int Cetnost(struct TData aData, unsigned *aVysl)
{
	if (aData.iData == NULL || aData.iPocet == 0)
	{
		return -1;
	}
	
	for (size_t i = 0; i < aData.iPocet; i++) // každý prvek v aData.iData
	{
		for (size_t t = 0; t < 10; t++) // Pro čísla 0-9
		{
			if (aData.iData[i] == t)
			{
				aVysl[t] = aVysl[t] + 1;
				// printf("\n%zu.|%zu : %ux|\n",i , t, aVysl[t]);
			}
		}
	}

	return 0;
}
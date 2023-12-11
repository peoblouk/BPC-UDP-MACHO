#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // pro funkce malloc(), free()
#include "check.h"// kontrola po alokaci 

struct TData { size_t iNum; char* iPtr; };
int data_read(FILE* aFile, struct TData *aData); // Funkce co bude èíst string ze souboru
int data_stat(const struct TData, size_t aStat[]); // Funkce na statické udáje asi

int main(int argc, char* argv[]) // argc a argv je prostì dané!
{
	struct TData data = { // Pomocná promìnná
		.iNum = 0,
		.iPtr = NULL
	};

	size_t stat[10] = {0};

	FILE* fr = fopen(argv[1], "r"); // otevøu soubor z pole argumentù argv[1] , 1 znaèí vstupního soubor, výstupní soubor by byl argv[2]
	if (fr == NULL) // oveøení zda se otevøelo 
	{
		return 1;
	}

	if (data_read(fr, &data) < 0) // Ètení dat ze souboru
	{
		return 2;
	}

	printf("znaky: "); 
	for (size_t i = 0; i < data.iNum; i++) // Výpis dat
	{
		printf("%c", data.iPtr[i]);
	}
	putchar('\n');

	if (data_stat(data, &stat) < 0) // Zpracování dat
	{
		free(data.iPtr);
		fclose(fr);
		return 3;
	}

	for (size_t i = 0; i < 10; i++)
	{
		printf("%zu : %zu\n", i, stat[i]);
	}
	
	fclose(fr);
	free(data.iPtr);
	return 0;
}

int data_read(FILE* aFile, struct TData *aData)
{
	if (aFile == NULL || aData == NULL) // Kontrola pøeètených 
	{
		return -1;
	}

	if (fscanf(aFile, "%zu", &aData->iNum) != 1 || fgetc(aFile) == EOF) // Ètení a zároveò
	{
	return -2;
	}

	aData->iPtr = malloc(aData->iNum * sizeof(struct TData)); // Dynamická alokace
	if (aData->iPtr == NULL) // Chyba alokace
	{
		aData->iNum = 0; // Nulování složky iNum
		return -3;
	}

	for (size_t i = 0; i < aData->iNum; i++) // Pøeètení N znakù
	{
		if (fscanf(aFile, "%c", &aData->iPtr[i]) != 1)
		{
			free(aData->iPtr);
			aData->iNum = NULL;
			aData->iPtr = NULL;
			return -4;
		}
	}

	return 0;
}

int data_stat(const struct TData aData, size_t aStat[])
{
	if (aData.iNum == 0 || aData.iPtr == NULL) // Kontrola pøedaných parametrù
	{
		return -1;
	}

	// Iterace 
	char cisla[] = "0123456789";
	char *cisla_ptr = &cisla;
	putchar('\n');

	for (size_t i = 0; i < aData.iNum; i++) // Pro iteruji celé pole
	{
		for (size_t t = 0; t < 10; t++)
		{
			if (aData.iPtr[i] == cisla_ptr[t])
			{
				aStat[t] += 1;
			}	
		}
	}

	return 0;
}
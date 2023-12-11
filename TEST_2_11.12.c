#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // pro funkce malloc(), free()
#include "check.h"// kontrola po alokaci 

struct TData { size_t iNum; char* iPtr; };
int data_read(FILE* aFile, struct TData *aData); // Funkce co bude ��st string ze souboru
int data_stat(const struct TData, size_t aStat[]); // Funkce na statick� ud�je asi

int main(int argc, char* argv[]) // argc a argv je prost� dan�!
{
	struct TData data = { // Pomocn� prom�nn�
		.iNum = 0,
		.iPtr = NULL
	};

	size_t stat[10] = {0};

	FILE* fr = fopen(argv[1], "r"); // otev�u soubor z pole argument� argv[1] , 1 zna�� vstupn�ho soubor, v�stupn� soubor by byl argv[2]
	if (fr == NULL) // ove�en� zda se otev�elo 
	{
		return 1;
	}

	if (data_read(fr, &data) < 0) // �ten� dat ze souboru
	{
		return 2;
	}

	printf("znaky: "); 
	for (size_t i = 0; i < data.iNum; i++) // V�pis dat
	{
		printf("%c", data.iPtr[i]);
	}
	putchar('\n');

	if (data_stat(data, &stat) < 0) // Zpracov�n� dat
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
	if (aFile == NULL || aData == NULL) // Kontrola p�e�ten�ch 
	{
		return -1;
	}

	if (fscanf(aFile, "%zu", &aData->iNum) != 1 || fgetc(aFile) == EOF) // �ten� a z�rove�
	{
	return -2;
	}

	aData->iPtr = malloc(aData->iNum * sizeof(struct TData)); // Dynamick� alokace
	if (aData->iPtr == NULL) // Chyba alokace
	{
		aData->iNum = 0; // Nulov�n� slo�ky iNum
		return -3;
	}

	for (size_t i = 0; i < aData->iNum; i++) // P�e�ten� N znak�
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
	if (aData.iNum == 0 || aData.iPtr == NULL) // Kontrola p�edan�ch parametr�
	{
		return -1;
	}

	// Iterace 
	char cisla[] = "0123456789";
	char *cisla_ptr = &cisla;
	putchar('\n');

	for (size_t i = 0; i < aData.iNum; i++) // Pro iteruji cel� pole
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
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // pro funkce malloc(), free()
#include "check.h"// kontrola po alokaci 

struct TData
{
	double* iPtr;
	size_t iNum;
};

int data_read(FILE* aFile, struct TData* aPtrData); // Funkce na ètení vstupních dat
int data_write(FILE* aFile, const struct TData aData); // Funkce na zápis dat do souboru

int data_minmax(const struct TData aData, double* aPtrMin, double* aPtrMax); // Funkce na nalezení minima a maxima
int data_minmax_write(FILE* aFile, double aMin, double aMax); // Funkce na tisk minima a maxima na rùzné výstupy
void data_destroy(struct TData* aPtrData); // Funkce na vymazání promìnných a alokaci

// V záložce properties>debugging>command argumnets //! jsme zadali cv11-1.exe vstup.txt vystup.txt 
/* Main */					
int main(int argc, char* argv[]) // argc a argv je prostì dané!
{

	/// Práce s vstupními argumenty /// 
	if (argc < 2) // kontrola poètu otevøených souborù (streamù)
	{
		fprintf(stderr, "Chyba - nebylo zadano jmeno vstupniho a vystupniho souboru");
		return 1;
	}

	/// Práce s vstupním souborem vstup.txt /// 
	FILE* fr = fopen(argv[1], "r"); // otevøu soubor z pole argumentù argv[1] , 1 znaèí vstupního soubor, výstupní soubor by byl argv[2]
	if (fr == NULL) // oveøení zda se otevøelo 
	{
		fprintf(stderr, "Chyba pri otevirani vstupniho souboru!\n"); // stderr chybový stream
		return 2;
	}

	/// Práce s dynamicky alokovaným polem /// 
	struct TData data = { 0,0 }; // Promìnná pro uložení 

	// Náhrada oproti CV11-3
	if(data_read(fr, &data) < 0) // Pøedám funkci file stream a adresu na promìnnou data, jelikož funkce parametr funkce je pointer
	{
		fprintf(stderr, "Chyba pri otevirani vstupniho souboru!\n"); // stderr chybový stream
		data_destroy(&data);
		fclose(fr);
	}
	data_destroy(&data);
	fclose(fr);

	
	double min, max; // pomocné promìnné
	if (data_minmax(data, &min, &max) < 0)
	{
		return 4;
	}

	data_minmax_write(stdout, min, max); // tisk na obrazovku
	

	FILE* fw = fopen(argv[2], "w"); // Otevøení výstupního souboru
	if (fw == NULL)
	{
		fprintf(stderr, "Chyba pri otevirani vystupniho souboru!\n");
		return 5;
	}

	if (data_minmax_write(fw, min, max) < 0)
	{
		fprintf(stderr, "Chyba pri zapisu do vystupniho souboru!\n");
		fclose(fw);
		return 6;
	}
	fclose(fw); // Uzavøení výstupního souboru

	return 0;
}

int data_read(FILE* aFile, struct TData* aPtrData)
{
	if(aFile == NULL || aPtrData == NULL)
	{
		fprintf(stderr, "Chyba pri otevirani vystupniho souboru!\n");
		printf("Špatnì pri cteni dat ze souboru");
		return -1;
	}

		// K prvku struktury pøes ukazatel musím použít ->
	if (fscanf(aFile, "%zu", &aPtrData->iNum) != 1) // Ètení poètu dat (na prvním øádku souboru vstup.txt je èíslo, které udává poèet)
	{
		// fprintf(stderr, "Chyba pri cteni poctu dat!\n");
		return -1;
	}

	aPtrData->iPtr = malloc(aPtrData->iNum * sizeof(double)); // Alokace pole pøes ukazatel
	if (aPtrData->iPtr == NULL) // Oveøení zda opravdu místo bylo alokováno
	{
		// printf("Chyba alokace!");
		return -1;
	}

	for (size_t i = 0; i < aPtrData->iNum; i++) {
		if (fscanf(aFile, "%lf", &aPtrData->iPtr[i]) != 1) // Ètení pole od uživatele
		{
			free(aPtrData->iPtr); // Ukonèení alokace, má smysl uvolnit jen pamì, která alokována
			// fprintf(stderr, "Chyba alokace!\n"); // Tisk do streamu souborù
			// fclose(fr); // Ukonèit ètení souboru
			aPtrData->iPtr = NULL; // Aby adresa nebyl zabraná
			aPtrData->iNum = 0;
			return -1;
		}
	}


	return 0;
}

int data_write(FILE* aFile, const struct TData aData) // Zápis dat
{
	if (aFile == NULL || aData.iPtr == NULL)
	{
		return -1;
	}

	for (size_t i = 0; i < aData.iNum; i++) // Kontrola ètení
	{
		if (fprintf(aFile, "%lf", aData.iPtr[i]) < 0)
		{
			return -1;
		}
	}
	if(fprintf(aFile, "\n") < 0) // Odøádkování
	{
		return -1;
	}

	return 0;
}

int data_minmax(const struct TData aData, double* aPtrMin, double* aPtrMax) // Funkce pro hledání minima a maxima v datech
{
	/// Zpracování vstupních dat funkce /// 
	if (aData.iPtr == NULL || aPtrMin == NULL || aPtrMax == NULL || aData.iNum == 0) // Kontrola
	{
		return -1;
	}
	*aPtrMin = *aPtrMax = aData.iPtr[0]; // zpracovani prvniho prvku

	/// Algoritmus pro hledání mininmální a maximální hodnoty /// 
	for (size_t i = 0; i < aData.iNum; i++) // vyhledávání min a max (algoritmus)
	{
		if (aData.iPtr[i] > *aPtrMax)
			*aPtrMax = aData.iPtr[i];
		else if (aData.iPtr[i] < *aPtrMin)
			*aPtrMin = aData.iPtr[i];
	}
	return 1;
}

int data_minmax_write(FILE* aFile, double aMin, double aMax)
{
	if (aFile == NULL) // Kontrola aFile
	{
		return -1;
	}

	if (fprintf(aFile, "min = % lf max = % lf\n", aMin, aMax) < 0)
	{
		fprintf(stderr, "Chyba pri zapisu do vystupniho souboru!\n");
		return -1;
	}

	if (fprintf(aFile, "min = % lf max = % lf\n", aMin, aMax) < 0) // zapiš na zvolený výstup informaci o min, max
	{
		return -1;
	}

	return 0;
}

void data_destroy(struct TData* aPtrData)
{
	if (aPtrData != NULL)
	{
		if (aPtrData->iPtr != NULL) 
		{
			free(aPtrData->iPtr);
			aPtrData->iPtr = NULL;
			aPtrData->iNum = 0;
		}
	}
}
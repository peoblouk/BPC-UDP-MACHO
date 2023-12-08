#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // pro funkce malloc(), free()
#include "check.h"// kontrola po alokaci 

int minmax(size_t aNum, double aData[aNum], double* aPtrmin, double* aPtrmax);

// V záložce properties>debugging>command argumnets //! jsme zadali cv11-1.exe vstup.txt vystup.txt 

int main(int argc, char* argv[]) // argc a argv je prostě dané!
{
	/// Práce s vstupními argumenty /// 
	if (argc < 2) // kontrola počtu otevřených souborů (streamů)
	{
		fprintf(stderr, "Chyba - nebylo zadano jmeno vstupniho a vystupniho souboru");
		return 1;
	}

	/// Práce s vstupním souborem vstup.txt /// 
	FILE* fr = fopen(argv[1], "r"); // otevřu soubor z pole argumentů argv[1] , 1 značí vstupního soubor, výstupní soubor by byl 2
	if (fr == NULL) // oveření zda se otevřelo 
	{
		fprintf(stderr, "Chyba pri otevirani vstupniho souboru!\n"); // stderr chybový stream

		return 2;
	}

	/// Práce s dynamicky alokovaným polem /// 
	double* ptr_data = NULL; // Proměnná pole později alokována
	size_t data_num = 0; // Proměnná pro uložení počtu čísel

	if (fscanf(fr, "%zu", &data_num) != 1) // Čtení počtu dat (na prvním řádku souboru vstup.txt je číslo, které udává počet)
	{
		fprintf(stderr, "Chyba pri cteni poctu dat!\n");
		return 3;
	}

	ptr_data = malloc(data_num * sizeof(double)); // Alokace pole pomocí 
	if (ptr_data == NULL) // Oveření zda opravdu místo bylo alokováno
	{
		printf("Chyba alokace!");
		return 4;
	}

	for (size_t i = 0; i < data_num; i++) {
		if (fscanf(fr, "%lf", &ptr_data[i]) != 1) // Čtení pole od uživatele
		{
			free(ptr_data); // Ukončení alokace, má smysl uvolnit jen paměť, která alokována
			fprintf(stderr, "Chyba alokace!\n"); // Tisk do streamu souborů
			fclose(fr); // Ukončit čtení souboru
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

	/// Práce s výstupním souborem vystup.txt /// 
	FILE* fw = fopen(argv[2], "w"); // Otevření výstupního souboru
	if (fw == NULL)
	{
		fprintf(stderr, "Chyba pri otevirani vystupniho souboru!\n");
		return 7;
	}

	if (fprintf(fw, "min = % lf max = % lf\n", min, max) < 0)
	{
		fprintf(stderr, "Chyba pri otevirani vystupniho souboru!\n");
		return 8;
	}

	fclose(fr); // Uzavření vstupního souboru
	fclose(fw); // Uzavření výstupního souboru
	free(ptr_data); // Uvolnění paměti po alokaci (dává když nebude třeba nebo ukončením programu)

	return 0;
}

int minmax(size_t aNum, double aData[aNum], double* aPtrmin, double* aPtrmax) // Funkce pro hledání minima a maxima
{
	/// Zpracování vstupních dat funkce /// 
	if (aData == NULL || aPtrmin == NULL || aPtrmax == NULL || aNum == 0) // Kontrola
	{
		return -1;
	}
	*aPtrmin = *aPtrmax = aData[0]; // zpracovani prvniho prvku

	/// Algoritmus pro hledání mininmální a maximální hodnoty /// 
	for (size_t i = 0; i < aNum; i++) // vyhledávání min a max (algoritmus)
	{
		if (aData[i] > *aPtrmax)
			*aPtrmax = aData[i];
		else if (aData[i] < *aPtrmin)
			*aPtrmin = aData[i];
	}
	return 1;
}
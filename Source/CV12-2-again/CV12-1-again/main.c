#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // pro funkce malloc(), free()
#include "check.h"// kontrola po alokaci 

struct TData
{
	double *iPtr_data; //
	size_t iData_num; // Počet prvků
};

int data_read(FILE* aFile, struct TData* aPtrData); // Čtení dat do pole a dynamická alokace 
// int data_write(FILE* aFile, const struct TData aData); // Zápis souborů do výstupního souboru //! NEMÁ ŽÁDNÉ VYUŽITÍ xD
int data_minmax(const struct TData aData, double* aPtrMin, double* aPtrMax); // Hledání min a max z množiny dat
int data_minmax_write(FILE* aFile, double aMin, double aMax); // Zápis do výstupního souboru
void data_destroy(struct TData* aPtrData); // Uvolnění pamětí a uzavření souborů

// V záložce properties>debugging>command argumnets //! jsme zadali vstup.txt vystup.txt 

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

	struct TData data = { 0,0 }; // Proměnná pro uložení 

	if (data_read(fr, &data) < 0)
	{
		fprintf(stderr, "Chyba pri otevirani vstupniho souboru!\n"); // stderr chybov� stream
		data_destroy(&data);
		fclose(fr); // Uzavření vstupního souboru
		return 3;
	}
	fclose(fr); // Konec práce se vstupním souborem

	double min, max;
	if (data_minmax(data, &min, &max) < 0)
	{
		data_destroy(&data);
		return 4;
	}

	printf("\nMin= %lf\n Max= %lf\n", min, max);

	/// Práce s výstupním souborem /// 
	FILE* fw = fopen(argv[2], "w"); // Otevření výstupního souboru
	if (fw == NULL)
	{
		fprintf(stderr, "Chyba pri otevirani vystupniho souboru!\n");
		return 5;
	}

	if (data_minmax_write(fw, min, max) < 0) // Zapsat data do souboru
	{
		data_destroy(&data);
		return 6;
	}

	fclose(fw); // Uzavření výstupního souboru
	data_destroy(&data);  // Uvolnění paměti po alokaci (dává když nebude třeba nebo ukončením programu)

	return 0;
}

int data_read(FILE* aFile, struct TData* aPtrData)
{
	if (aFile == NULL || aPtrData == NULL) // Chyba při čtení vstupních dat
	{
		return -1;
	}

	if (fscanf(aFile, "%zu", &aPtrData->iData_num) != 1) // Čtení počtu dat (na prvním řádku souboru vstup.txt je číslo, které udává počet)
	{
		return -1;
	}

	aPtrData->iPtr_data = malloc(aPtrData->iData_num * sizeof(double)); // Dynamická alokace (funkce malloc vrací ukazatel na první adresu alokovaného pole)
	if (aPtrData->iPtr_data == NULL) // Ove�en� zda opravdu m�sto bylo alokov�no
	{
		return -1;
	}

	for (size_t i = 0; i < aPtrData->iData_num; i++) // Čtení jednotlivých hodnot
	{
		if (fscanf(aFile, "%lf", &aPtrData->iPtr_data[i]) != 1)
		{
			free(aPtrData->iPtr_data);
			return -1;
		}
		// printf("aPtrData[%zu]%lf", i ,aPtrData->iPtr_data[i]);
	}
	putchar('\n');

	return 0;
}

/* int data_write(FILE* aFile, const struct TData aData)
{
	if (aFile == NULL || aData.iPtr_data == NULL) // Chyba při čtení vstupních dat
	{
		return -1;
	}

	for (size_t i = 0; i < aData.iData_num; i++)
	{
		if(fprintf(aFile, "%lf", aData.iPtr_data[i]) < 0)
		{
			return -1;
		}
	}
	return 0;
} */

int data_minmax(const struct TData aData, double* aPtrMin, double* aPtrMax)
{
	/// Zpracování vstupních dat funkce /// 
	if (aData.iPtr_data == NULL || aPtrMin == NULL || aPtrMax == NULL || aData.iData_num == 0) // Kontrola
	{
		return -1;
	}
	// printf("\nx = %lf\n", aData.iPtr_data[0]);
	*aPtrMin = *aPtrMax = aData.iPtr_data[0]; // zpracovani prvniho prvku

	/// Algoritmus pro hledání mininmální a maximální hodnoty /// 
	for (size_t i = 0; i < aData.iData_num; i++) // vyhledávání min a max (algoritmus)
	{
		if (aData.iPtr_data[i] > *aPtrMax)
			*aPtrMax = aData.iPtr_data[i];
		else if (aData.iPtr_data[i] < *aPtrMin)
			*aPtrMin = aData.iPtr_data[i];
	}

	return 1;
}

int data_minmax_write(FILE* aFile, double aMin, double aMax)
{
	if (aFile == NULL) // Chyba při čtení vstupních dat
	{
		return -1;
	}

	if (fprintf(aFile, "Min= %lf\n Max= %lf", aMin, aMax) < 0)
	{
		return -1;
	}

	return 0;
}

void data_destroy(struct TData* aPtrData)
{
	if (aPtrData != NULL)
	{
		if (aPtrData->iPtr_data != NULL)
		{
			free(aPtrData->iPtr_data);
			aPtrData->iPtr_data = NULL;
			aPtrData->iData_num = 0;
		}
	}
}
#include "TData.h"

int data_read(FILE* aFile, struct TData* aPtrData)
{
	if (aFile == NULL || aPtrData == NULL)
	{
		fprintf(stderr, "Chyba pri otevirani vystupniho souboru!\n");
		printf("spatne pri cteni dat ze souboru");
		return -1;
	}

	// K prvku struktury p�es ukazatel mus�m pou��t ->
	if (fscanf(aFile, "%zu", &aPtrData->iNum) != 1) // �ten� po�tu dat (na prvn�m ��dku souboru vstup.txt je ��slo, kter� ud�v� po�et)
	{
		// fprintf(stderr, "Chyba pri cteni poctu dat!\n");
		return -1;
	}

	aPtrData->iPtr = malloc(aPtrData->iNum * sizeof(double)); // Alokace pole p�es ukazatel
	if (aPtrData->iPtr == NULL) // Ove�en� zda opravdu m�sto bylo alokov�no
	{
		// printf("Chyba alokace!");
		return -1;
	}

	for (size_t i = 0; i < aPtrData->iNum; i++) {
		if (fscanf(aFile, "%lf", &aPtrData->iPtr[i]) != 1) // �ten� pole od u�ivatele
		{
			free(aPtrData->iPtr); // Ukon�en� alokace, m� smysl uvolnit jen pam�, kter� alokov�na
			// fprintf(stderr, "Chyba alokace!\n"); // Tisk do streamu soubor�
			// fclose(fr); // Ukon�it �ten� souboru
			aPtrData->iPtr = NULL; // Aby adresa nebyl zabran�
			aPtrData->iNum = 0;
			return -1;
		}
	}


	return 0;
}

int data_write(FILE* aFile, const struct TData aData)
{
	if (aFile == NULL || aData.iPtr == NULL)
	{
		return -1;
	}

	for (size_t i = 0; i < aData.iNum; i++) // Kontrola �ten�
	{
		if (fprintf(aFile, "%lf", aData.iPtr[i]) < 0)
		{
			return -1;
		}
	}
	if (fprintf(aFile, "\n") < 0) // od��dkov�n�
	{
		return -1;
	}

	return 0;
}

int data_minmax(const struct TData aData, double* aPtrMin, double* aPtrMax) // Funkce pro hled�n� minima a maxima v datech
{
	/// Zpracov�n� vstupn�ch dat funkce /// 
	if (aData.iPtr == NULL || aPtrMin == NULL || aPtrMax == NULL || aData.iNum == 0) // Kontrola
	{
		return -1;
	}
	*aPtrMin = *aPtrMax = aData.iPtr[0]; // zpracovani prvniho prvku

	/// Algoritmus pro hled�n� mininm�ln� a maxim�ln� hodnoty /// 
	for (size_t i = 0; i < aData.iNum; i++) // vyhled�v�n� min a max (algoritmus)
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

	if (fprintf(aFile, "min = % lf max = % lf\n", aMin, aMax) < 0) // zapi� na zvolen� v�stup informaci o min, max
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
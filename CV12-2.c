#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // pro funkce malloc(), free()
#include "check.h"// kontrola po alokaci 

struct TData
{
	double* iPtr;
	size_t iNum;
};

int data_read(FILE* aFile, struct TData* aPtrData); // Funkce na �ten� vstupn�ch dat
int data_write(FILE* aFile, const struct TData aData); // Funkce na z�pis dat do souboru

int data_minmax(const struct TData aData, double* aPtrMin, double* aPtrMax); // Funkce na nalezen� minima a maxima
int data_minmax_write(FILE* aFile, double aMin, double aMax); // Funkce na tisk minima a maxima na r�zn� v�stupy
void data_destroy(struct TData* aPtrData); // Funkce na vymaz�n� prom�nn�ch a alokaci

// V z�lo�ce properties>debugging>command argumnets //! jsme zadali cv11-1.exe vstup.txt vystup.txt 
/* Main */					
int main(int argc, char* argv[]) // argc a argv je prost� dan�!
{

	/// Pr�ce s vstupn�mi argumenty /// 
	if (argc < 2) // kontrola po�tu otev�en�ch soubor� (stream�)
	{
		fprintf(stderr, "Chyba - nebylo zadano jmeno vstupniho a vystupniho souboru");
		return 1;
	}

	/// Pr�ce s vstupn�m souborem vstup.txt /// 
	FILE* fr = fopen(argv[1], "r"); // otev�u soubor z pole argument� argv[1] , 1 zna�� vstupn�ho soubor, v�stupn� soubor by byl argv[2]
	if (fr == NULL) // ove�en� zda se otev�elo 
	{
		fprintf(stderr, "Chyba pri otevirani vstupniho souboru!\n"); // stderr chybov� stream
		return 2;
	}

	/// Pr�ce s dynamicky alokovan�m polem /// 
	struct TData data = { 0,0 }; // Prom�nn� pro ulo�en� 

	// N�hrada oproti CV11-3
	if(data_read(fr, &data) < 0) // P�ed�m funkci file stream a adresu na prom�nnou data, jeliko� funkce parametr funkce je pointer
	{
		fprintf(stderr, "Chyba pri otevirani vstupniho souboru!\n"); // stderr chybov� stream
		data_destroy(&data);
		fclose(fr);
	}
	data_destroy(&data);
	fclose(fr);

	
	double min, max; // pomocn� prom�nn�
	if (data_minmax(data, &min, &max) < 0)
	{
		return 4;
	}

	data_minmax_write(stdout, min, max); // tisk na obrazovku
	

	FILE* fw = fopen(argv[2], "w"); // Otev�en� v�stupn�ho souboru
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
	fclose(fw); // Uzav�en� v�stupn�ho souboru

	return 0;
}

int data_read(FILE* aFile, struct TData* aPtrData)
{
	if(aFile == NULL || aPtrData == NULL)
	{
		fprintf(stderr, "Chyba pri otevirani vystupniho souboru!\n");
		printf("�patn� pri cteni dat ze souboru");
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

int data_write(FILE* aFile, const struct TData aData) // Z�pis dat
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
	if(fprintf(aFile, "\n") < 0) // Od��dkov�n�
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
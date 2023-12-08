#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // pro funkce malloc(), free() - dynamickou alokaci
#include "check.h"// kontrola po alokaci 

//Description program p�e�te dva vektory, ka�d� vektor m� iN slo�ek

// TVects obsahuje dva vektory, kdy ka�d� vektor m� iN prvk�(slo�ek v1, v2...)
struct TVects { size_t iN; int* iV1; int* iV2; int iProd;}; // iN - po�et prvk� vektoru, iV1 - pointer na za�atek prvn�ho vektoru, iV2 - pointer druh�ho vektoru, iProd - v�sledn� skal�rn� sou�in
int read_vect(FILE* aFr, size_t aN, int aVect[]); // �ten� vektor� ze souboru, aFr - pointer na file, aN - po�et prvk� vektor�, aVect - pole obasahuj�c� prvky vektor�
int print_vect(size_t aN, int *aVect[]); // Tisk vektor�, aN - po�et prvk� vektor�
int product_vect(struct TVects *aVects, int *aProd); // Skal�rn� sou�in vektor�

int main(int argc, char* argv[]) // argc a argv je prost� dan�!
{
	if (argc < 1) // Kontrola po�tu otev�en�ch soubor� (stream�)
	{
		fprintf(stderr, "Neni zadano jmeno vstupniho souboru");
		return 1;
	}

	FILE* fr = fopen(argv[1], "r"); // Otev�en� souboru z pole argument� argv[1]
	if (fr == NULL) // ove�en� zda se otev�elo 
	{
		fprintf(stderr, "Nelze otevrit %c\n", *argv[1]); // stderr chybov� stream
		return 2;
	}

	struct TVects vects = {
		.iN = 0, // Po�et prvk� ve vektoru
		.iV1 = NULL, // Prvn� vektor
		.iV2 = NULL, // Druh� vektor
		.iProd = 0
	};

	if (read_vect(fr, 2, ) < 0) // �ten� vektor� ze vstupn�ho souboru
	{
		return 3;
	}

	vects.iV1 = malloc(vects.iN * sizeof(int)); // Alokace pole
	vects.iV2 = malloc(vects.iN * sizeof(int)); // Alokace pole

	if (vects.iV1 == NULL) // Ove�en� zda opravdu m�sto bylo alokov�no
	{
		// printf("Chyba alokace!");
		return -1;
	}

	print_vect(vects.iN, vects.iV1);
	// {}

	fclose(fr); // Uzav�en� vstupn�ho souboru
	return 0;
}

int read_vect(FILE* aFr, size_t aN, int aVect[])
{
	if (aFr == NULL || aVect == 0 || aN == 0) // Kontrola zda funkci nep�ed�v�m pr�zdn� polo�ky
	{
		return -1;
	}

	if ((fscanf(aFr, "%zu", &aN)) != 1)
	{
		return -2;
	}
	
	for (size_t i = 0; i < aN; i++)
	{
		if (fscanf(aFr, "%d", &aVect[i]) != 1) // Kontrola zda byla p�e�tena slo�ka vektoru
		{
			return -2;
		}
	}

	return 0;
}

int print_vect(size_t aN, int *aVect[])
{
	if (aVect == NULL || aN == 0) // Kontrola zda funkci nep�ed�v�m pr�zdn� polo�ky
	{
		return -1;
	}
	for (size_t i = 0; i < aN; i++) 
	{	
		fprintf(stdout, "v[%zu]= %d %d\n", i, *aVect[0], *aVect[1]);
	}
	return 0;
}

int product_vect(struct TVects *aVects, int* aProd)
{
	if (aVects->iV1 == NULL || aVects->iV2 == NULL || aVects->iN == 0 || aVects->iProd == 0) // Kontrola zda funkci nep�ed�v�m pr�zdn� polo�ky
	{
		return -1;
	}

	aVects->iProd = ((aVects->iV1[0] * aVects->iV2[0]) + (aVects->iV1[1] * aVects->iV2[1])); // Skal�rn� sou�in

	return 0;
}

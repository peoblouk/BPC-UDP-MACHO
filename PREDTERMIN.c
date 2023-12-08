#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // pro funkce malloc(), free() - dynamickou alokaci
#include "check.h"// kontrola po alokaci 

//Description program pøeète dva vektory, každý vektor má iN složek

// TVects obsahuje dva vektory, kdy každý vektor má iN prvkù(složek v1, v2...)
struct TVects { size_t iN; int* iV1; int* iV2; int iProd;}; // iN - poèet prvkù vektoru, iV1 - pointer na zaèatek prvního vektoru, iV2 - pointer druhého vektoru, iProd - výsledný skalární souèin
int read_vect(FILE* aFr, size_t aN, int aVect[]); // Ètení vektorù ze souboru, aFr - pointer na file, aN - poèet prvkù vektorù, aVect - pole obasahující prvky vektorù
int print_vect(size_t aN, int *aVect[]); // Tisk vektorù, aN - poèet prvkù vektorù
int product_vect(struct TVects *aVects, int *aProd); // Skalární souèin vektorù

int main(int argc, char* argv[]) // argc a argv je prostì dané!
{
	if (argc < 1) // Kontrola poètu otevøených souborù (streamù)
	{
		fprintf(stderr, "Neni zadano jmeno vstupniho souboru");
		return 1;
	}

	FILE* fr = fopen(argv[1], "r"); // Otevøení souboru z pole argumentù argv[1]
	if (fr == NULL) // oveøení zda se otevøelo 
	{
		fprintf(stderr, "Nelze otevrit %c\n", *argv[1]); // stderr chybový stream
		return 2;
	}

	struct TVects vects = {
		.iN = 0, // Poèet prvkù ve vektoru
		.iV1 = NULL, // První vektor
		.iV2 = NULL, // Druhý vektor
		.iProd = 0
	};

	if (read_vect(fr, 2, ) < 0) // Ètení vektorù ze vstupního souboru
	{
		return 3;
	}

	vects.iV1 = malloc(vects.iN * sizeof(int)); // Alokace pole
	vects.iV2 = malloc(vects.iN * sizeof(int)); // Alokace pole

	if (vects.iV1 == NULL) // Oveøení zda opravdu místo bylo alokováno
	{
		// printf("Chyba alokace!");
		return -1;
	}

	print_vect(vects.iN, vects.iV1);
	// {}

	fclose(fr); // Uzavøení vstupního souboru
	return 0;
}

int read_vect(FILE* aFr, size_t aN, int aVect[])
{
	if (aFr == NULL || aVect == 0 || aN == 0) // Kontrola zda funkci nepøedávám prázdné položky
	{
		return -1;
	}

	if ((fscanf(aFr, "%zu", &aN)) != 1)
	{
		return -2;
	}
	
	for (size_t i = 0; i < aN; i++)
	{
		if (fscanf(aFr, "%d", &aVect[i]) != 1) // Kontrola zda byla pøeètena složka vektoru
		{
			return -2;
		}
	}

	return 0;
}

int print_vect(size_t aN, int *aVect[])
{
	if (aVect == NULL || aN == 0) // Kontrola zda funkci nepøedávám prázdné položky
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
	if (aVects->iV1 == NULL || aVects->iV2 == NULL || aVects->iN == 0 || aVects->iProd == 0) // Kontrola zda funkci nepøedávám prázdné položky
	{
		return -1;
	}

	aVects->iProd = ((aVects->iV1[0] * aVects->iV2[0]) + (aVects->iV1[1] * aVects->iV2[1])); // Skalární souèin

	return 0;
}

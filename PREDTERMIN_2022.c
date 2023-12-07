#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // pro funkce malloc(), free() - dynamickou alokaci
#include "check.h"// kontrola po alokaci 

//Description program pøeète dva vektory, každý vektor má iN složek

// TVects obsahuje dva vektory, kdy každý vektor má iN prvkù(složek v1, v2...)
struct TVects { size_t iN; int* iV1; int* iV2; int iProd;}; // iN - poèet prvkù vektoru, iV1 - pointer na zaèatek prvního vektoru, iV2 - pointer druhého vektoru, iProd - výsledný skalární souèin
int read_vect(FILE* aFr, size_t aN, int aVect[aN]); // Ètení vektorù ze souboru, aFr - pointer na file, aN - poèet prvkù vektorù, aVect - pole obasahující prvky vektorù
int print_vect(size_t aN, int aVect[aN]); // Tisk vektorù, aN - poèet prvkù vektorù
int product_vect(struct TVects aVects, int *aProd); // Skalární souèin vektorù

int main(int argc, char* argv[]) // argc a argv je prostì dané!
{
	if (argc < 2) // Kontrola poètu otevøených souborù (streamù)
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

	if (fscanf(fr, "%zu", &vects.iN) != 1)
	{
		return 3;// Ètení zde vstupního streamu èísla iN
	}

	vects.iV1 = malloc(vects.iN * sizeof(int)); // Alokace pole
	vects.iV2 = malloc(vects.iN * sizeof(int)); // Alokace pole

	if (vects.iV1 == NULL) // Oveøení zda opravdu místo bylo alokováno
	{
		return 4;
	}

	if (read_vect(fr, vects.iN, vects.iV1) < 0) // Ètení vektor ze vstupního souboru
	{
		free(vects.iV1);
		free(vects.iV2);
		return 5;
	}

	if (read_vect(fr, vects.iN, vects.iV2) < 0) // Ètení vektor ze vstupního souboru
	{
		free(vects.iV1);
		free(vects.iV2);
		return 5;
	}

	print_vect(vects.iN, vects.iV1);
	print_vect(vects.iN, vects.iV2);

	fprintf(stdout, "Soucin: %d\n", vects.iProd); // stderr chybový stream
	if((product_vect(vects, &vects.iProd)) < 0)
	{
		free(vects.iV1);
		free(vects.iV2);
		fclose(fr);
		return 6;
	}


	free(vects.iV1);
	free(vects.iV2);
	fclose(fr); // Uzavøení vstupního souboru
	return 0;
}

int read_vect(FILE* aFr, size_t aN, int aVect[aN]) // VLA - clang , pole je pointer na místo pamìti
{
	if (aFr == NULL || (aVect == NULL && aN == 0)) // Kontrola zda funkci nepøedávám prázdné položky
	{
		return -1;
	}

	for (size_t i = 0; i < aN; i++)
	{
		
		if (fscanf(aFr, "%d", &aVect[i]) != 1) // Kontrola zda byla pøeètena složka vektoru
		{
			return -2;
		}
	}

	/* for (size_t z = 0; z < aN; z++)
	printf("%d,", aVect[z]); */

	return 0;
}

int print_vect(size_t aN, int aVect[aN]) // VLA - variable lenght array , tisk jednoho vektoru
{
	if (aVect == NULL || aN == 0) // Kontrola zda funkci nepøedávám prázdné položky
	{
		return -1;
	}

	for (size_t i = 0; i < aN; i++) 
	{	
		fprintf(stdout, "%d ", aVect[i]);
	}
	putchar('\n');
	return 0;
}

int product_vect(struct TVects aVects, int* aProd)
{
	// printf("%d", aVects.iV1);

	if (aVects.iV1 == NULL || aVects.iV2 == NULL || aVects.iN == 0 || aProd == NULL) // Kontrola zda funkci nepøedávám prázdné položky
	{
		return -1;
	}

	*aProd = ((aVects.iV1[0] * aVects.iV2[0]) + (aVects.iV1[1] * aVects.iV2[1])); // Skalární souèin
	return 0;
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // pro funkce malloc(), free() - dynamickou alokaci
#include "check.h"// kontrola po alokaci 

//Description program p�e�te dva vektory, ka�d� vektor m� iN slo�ek

// TVects obsahuje dva vektory, kdy ka�d� vektor m� iN prvk�(slo�ek v1, v2...)
struct TVects { size_t iN; int* iV1; int* iV2; int iProd;}; // iN - po�et prvk� vektoru, iV1 - pointer na za�atek prvn�ho vektoru, iV2 - pointer druh�ho vektoru, iProd - v�sledn� skal�rn� sou�in
int read_vect(FILE* aFr, size_t aN, int aVect[aN]); // �ten� vektor� ze souboru, aFr - pointer na file, aN - po�et prvk� vektor�, aVect - pole obasahuj�c� prvky vektor�
int print_vect(size_t aN, int aVect[aN]); // Tisk vektor�, aN - po�et prvk� vektor�
int product_vect(struct TVects aVects, int *aProd); // Skal�rn� sou�in vektor�

int main(int argc, char* argv[]) // argc a argv je prost� dan�!
{
	if (argc < 2) // Kontrola po�tu otev�en�ch soubor� (stream�)
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

	if (fscanf(fr, "%zu", &vects.iN) != 1)
	{
		return 3;// �ten� zde vstupn�ho streamu ��sla iN
	}

	vects.iV1 = malloc(vects.iN * sizeof(int)); // Alokace pole
	vects.iV2 = malloc(vects.iN * sizeof(int)); // Alokace pole

	if (vects.iV1 == NULL) // Ove�en� zda opravdu m�sto bylo alokov�no
	{
		return 4;
	}

	if (read_vect(fr, vects.iN, vects.iV1) < 0) // �ten� vektor ze vstupn�ho souboru
	{
		free(vects.iV1);
		free(vects.iV2);
		return 5;
	}

	if (read_vect(fr, vects.iN, vects.iV2) < 0) // �ten� vektor ze vstupn�ho souboru
	{
		free(vects.iV1);
		free(vects.iV2);
		return 5;
	}

	print_vect(vects.iN, vects.iV1);
	print_vect(vects.iN, vects.iV2);

	fprintf(stdout, "Soucin: %d\n", vects.iProd); // stderr chybov� stream
	if((product_vect(vects, &vects.iProd)) < 0)
	{
		free(vects.iV1);
		free(vects.iV2);
		fclose(fr);
		return 6;
	}


	free(vects.iV1);
	free(vects.iV2);
	fclose(fr); // Uzav�en� vstupn�ho souboru
	return 0;
}

int read_vect(FILE* aFr, size_t aN, int aVect[aN]) // VLA - clang , pole je pointer na m�sto pam�ti
{
	if (aFr == NULL || (aVect == NULL && aN == 0)) // Kontrola zda funkci nep�ed�v�m pr�zdn� polo�ky
	{
		return -1;
	}

	for (size_t i = 0; i < aN; i++)
	{
		
		if (fscanf(aFr, "%d", &aVect[i]) != 1) // Kontrola zda byla p�e�tena slo�ka vektoru
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
	if (aVect == NULL || aN == 0) // Kontrola zda funkci nep�ed�v�m pr�zdn� polo�ky
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

	if (aVects.iV1 == NULL || aVects.iV2 == NULL || aVects.iN == 0 || aProd == NULL) // Kontrola zda funkci nep�ed�v�m pr�zdn� polo�ky
	{
		return -1;
	}

	*aProd = ((aVects.iV1[0] * aVects.iV2[0]) + (aVects.iV1[1] * aVects.iV2[1])); // Skal�rn� sou�in
	return 0;
}

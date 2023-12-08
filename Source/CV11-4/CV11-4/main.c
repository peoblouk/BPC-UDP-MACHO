#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // pro funkce malloc(), free()
#include <math.h> // pro funkci hypot
#include "check.h"// kontrola po alokaci 

struct TPoint { // struktura s hodnoty bodů
	double iX;
	double iY;
};


int main(int argc, char* argv[])
{
	if (argc < 2) // kontrola počtu otevřených souborů (streamů)
	{
		fprintf(stderr, "Chyba - nebylo zadano jmeno vstupniho souboru");
		return 1;
	}

	struct TPoint* points_ptr = NULL;
	FILE* fr = fopen(argv[1], "r"); // otevřu soubor z pole argumentů argv[1] , 1 značí vstupního soubor, výstupní s
	
	if (fr == NULL) // oveření zda se otevřelo 
	{
		fprintf(stderr, "Chyba pri otevirani vstupniho souboru!\n"); // stderr chybový stream
		return 2;
	}


	size_t point_num = 0;
	if (fscanf(fr, "%zu", &point_num) != 1) // Čtení počtu dat (na prvním řádku souboru vstup.txt je číslo, které udává počet)
	{
		fprintf(stderr, "Chyba pri cteni poctu dat!\n");
		fclose(fr);
		return 3;
	}

	points_ptr = malloc(point_num *sizeof(struct TPoint)); // Alokace pole pomocí 
	if (points_ptr == NULL) // Oveření zda opravdu místo bylo alokováno
	{
		printf("Chyba alokace!");
		fclose(fr);
		return 4;
	}

	for (size_t i = 0; i < point_num; i++) {
		if (fscanf(fr, "%lf%lf", &points_ptr[i].iX, &points_ptr[i].iY) != 2) // Čtení pole od uživatele
		{
			free(points_ptr); // Ukončení alokace, má smysl uvolnit jen paměť, která alokována
			fprintf(stderr, "Chyba alokace!\n"); // Tisk do streamu souborů
			fclose(fr); // Ukončit čtení souboru
			return 3;
		}
	}


	fclose(fr);

	for (size_t i = 0; i < point_num; i++)
	{
		;
		printf("x=%lf y=%lf |d|=%lf\n", points_ptr[i].iX, points_ptr[i].iY, hypot(points_ptr[i].iX,points_ptr[i].iY));
	}

	free(points_ptr);
	return 0;
}
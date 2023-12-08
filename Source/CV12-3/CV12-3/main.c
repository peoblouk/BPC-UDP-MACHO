#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // pro funkce malloc(), free()
#include "TData.h"
#include "check.h"// kontrola po alokaci 


// V z�lo�ce properties>debugging>command argumnets //! jsme zadali vstup.txt vystup.txt 

int main(int argc, char* argv[]) // argc a argv je prostě dané!
{
	/// Práce s vstupními argumenty /// 
	if (argc < 2) // kontrola počtu otevřených souborů (streamů)
	{
		fprintf(stderr, "Chyba - nebylo zadano jmeno vstupniho a vystupniho souboru");
		return 1;
	}

	/// Práce s vstupním souborem vstup.txt /// 
	FILE* fr = fopen(argv[1], "r"); // otevřu soubor z pole argumentů argv[1] , 1 značí vstupního soubor, výstupní soubor by byl argv[2]
	if (fr == NULL) // oveření zda se otevřelo 
	{
		fprintf(stderr, "Chyba pri otevirani vstupniho souboru!\n"); // stderr chybový stream
		return 2;
	}

	/// Práce s dynamicky alokovaným polem /// 
	struct TData data = { 0,0 }; // Proměnná pro uložení 

	// Náhrada oproti CV11-3
	if (data_read(fr, &data) < 0) // Předám funkci file stream a adresu na proměnnou data, jelikož funkce parametr funkce je pointer
	{
		fprintf(stderr, "Chyba pri otevirani vstupniho souboru!\n"); // stderr chybový stream
		data_destroy(&data);
		fclose(fr);
	}
	data_destroy(&data);
	fclose(fr);


	double min, max; // pomocné proměnné
	if (data_minmax(data, &min, &max) < 0)
	{
		return 4;
	}

	data_minmax_write(stdout, min, max); // tisk na obrazovku


	FILE* fw = fopen(argv[2], "w"); // Otevření výstupního souboru
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
	fclose(fw); // Uzavření výstupního souboru

	return 0;
}
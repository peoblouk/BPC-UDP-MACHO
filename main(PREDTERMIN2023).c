#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // pro funkce malloc(), free()
#include "check.h"// kontrola po alokaci 
#include "TData.h"
// #include "math.h"

int main(int argc, char* argv[])
{
	size_t num = 0;
	struct TData* data = NULL;

	if (argc < 1) // Kontrola vstupních parametrů
	{
		fprintf(stderr, "Neni zadano jmeno souboru\n");
		return 1;
	}

	FILE* fr = fopen(argv[1], "r");
	if (fr == NULL) // ove�en� zda se otev�elo 
	{
		fprintf(stderr, "Nelze otevrit vstupní soubor\n");
		return 2;
	}

	if (fscanf(fr, "%zu", &num) != 1) // cteni poctu dat
	{
		return 3;
	}

	data = malloc(num * sizeof(struct TData)); // Dynamická alokace

	if (data == NULL)
	{
		fclose(fr);
		return 4;
	}

	for (size_t i = 0; i < num; i++) // Čtení prvků
	{
		if (data_read(fr, &data[i]) < 0)
		{
			fclose(fr);
			free(data);
			return 5;
		}
	}
	fclose(fr);

	float mean_val; // pomocná proměnná

	if (data_mean(num, data, &mean_val) < 0)
	{
		free(data);
		return 6;
	}

	putchar('\n');

	for (size_t i = 0; i < num; i++)
	{
		printf("{.iID = %u, .iData = %s, .iValue= %f }\n", data[i].iID, data[i].iDateStr, data[i].iValue);
	}
	printf("Mean value: %f", mean_val);
	
	free(data);
	return 0;
}


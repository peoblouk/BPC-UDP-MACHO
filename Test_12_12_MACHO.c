#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // pro funkce malloc(), free()
#include "check.h"// kontrola po alokaci 
#include "math.h"

struct TPoint { double iX; double iY; };
struct TLine { struct TPoint iA; struct TPoint iB; };

int line_read(FILE* aFile, struct TLine* aLine);
static inline double line_lenght(const struct TLine aLine);

int main(void)
{
	struct TLine* lines = NULL;
	size_t line_num = 0;

	FILE* fr = fopen("data.txt", "r"); // otevøu soubor z pole argumentù argv[1] , 1 znaèí vstupního soubor, výstupní soubor by byl argv[2]
	if (fr == NULL) // oveøení zda se otevøelo 
	{
		return 1;
	}

	if (fscanf(fr, "%zu", &line_num) != 1) // Ètení poètu dat (na prvním øádku souboru vstup.txt je èíslo, které udává poèet)
	{
		return 2;
	}

	lines = malloc(line_num * sizeof(struct TLine));
	if (lines == NULL)
	{
		return 3;
	}

	for (size_t i = 0; i < line_num; i++)
	{
		if (line_read(fr, &lines[i]) < 0)
		{
			fclose(fr);
			free(lines);
			return 4;
		}
	}
	fclose(fr);

	for (size_t i = 0; i < line_num; i++)
	{
		printf("[%lf, %lf] [%lf, %lf] : %lf", lines[i].iA.iX, lines[i].iA.iY, lines[i].iB.iX, lines[i].iB.iY, line_lenght(lines[i]));
		putchar('\n');
	}

	free(lines);
	return 0;
}

int line_read(FILE* aFile, struct TLine* aLine)
{
	if (aFile == NULL || aLine == NULL)
	{
		return -1;
	}

	if (fscanf(aFile, "%lf %lf %lf %lf", &aLine->iA.iX, &aLine->iA.iY, &aLine->iB.iX, &aLine->iB.iY) != 4) // Ètení bodù A a B
	{
		return -2;
	}
	// printf("%lf %lf %lf %lf", aLine->iA.iX, aLine->iA.iY, aLine->iB.iX, aLine->iB.iY);

	return 0;
}

static inline double line_lenght(const struct TLine aLine)
{
	double delka;

	delka = hypot(aLine.iB.iX - aLine.iA.iX, aLine.iB.iY - aLine.iA.iY);

	return delka;
}
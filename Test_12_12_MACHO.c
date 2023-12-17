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

	FILE* fr = fopen("data.txt", "r"); // otev�u soubor z pole argument� argv[1] , 1 zna�� vstupn�ho soubor, v�stupn� soubor by byl argv[2]
	if (fr == NULL) // ove�en� zda se otev�elo 
	{
		return 1;
	}

	if (fscanf(fr, "%zu", &line_num) != 1) // �ten� po�tu dat (na prvn�m ��dku souboru vstup.txt je ��slo, kter� ud�v� po�et)
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

	if (fscanf(aFile, "%lf %lf %lf %lf", &aLine->iA.iX, &aLine->iA.iY, &aLine->iB.iX, &aLine->iB.iY) != 4) // �ten� bod� A a B
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
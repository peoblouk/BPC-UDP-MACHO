// Author: Petr Oblouk

#include <stdio.h>

#define ROWS 2
#define COLS 3

void tisk_matice(int mat[ROWS][COLS]) 	// tisk matice
{
	for (size_t row = 0; row < ROWS; row++)
	{
		for (size_t cols = 0; cols < COLS; cols++)
		{
			printf("%d ", mat[row][cols]);
		}
		printf("\n");
	}
}

int main(void)
{
	int matA[ROWS][COLS] =
	{
		{ 1, 2, 3 },
		{ 4, 5, 6 }
	};

	int matB[ROWS][COLS] =
	{
		{ 10, 20, 30 },
		{ 40, 50, 60 },
	};
	int matC[ROWS][COLS];

	printf("Matice A\n");
	tisk_matice(matA);
	printf("\n");

	printf("Matice B\n");
	tisk_matice(matB);
	printf("\n");

	// soucet matic
	for (size_t row = 0; row < ROWS; row++)
	{
		for (size_t cols = 0; cols < COLS; cols++)
		{
			matC[row][cols] = matA[row][cols] + matB[row][cols];
		}
	}
	printf("Matice C\n");
	tisk_matice(matC);
}

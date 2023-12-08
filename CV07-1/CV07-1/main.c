#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)

#define MIN -4.0
#define MAX 5.0
#define N 6

{
	double data[N];

	printf("Zadej %zu cisel v intervalu (%lf, %lf): \n", (size_t)N, MIN, MAX); // pro indexování pole 
	size_t i = 0;
	while (i < N)
	{
		double x;
		if (scanf("%lf", &x) != 1)
		{
			printf("Chyba - nebylo zadano cislo! \n");
		}

		else if (x >= MIN && x <= MAX) 
		{
			data[i] = x;
			i++;
		}
		else
		{
			printf("Chyba - zadej cislo v intervalu (%lf, %lf: ", MIN, MAX);
		}
	}
	for (size_t i = 0;i < N; i++)
		printf("%lf", data[i]);
		
	putchar("\n"); //vytiskne jeden znak pouze lehčí forma tiskne na řádek
	
	double min, max;
	min = max = data[0]; // zpracovani prvniho prvku
	
	for (size_t i = 0; i < N; i++) // vyhledávání min a max
	{
		if (data[i] > max)
			max = data[i];
		else if (data[i] < min)
			min = data[i];
	}
	printf("\n min= %lf max= %lf\n", min, max);

	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>

int main(void)
{
	unsigned u, w, r;
	r = 0;
	printf("Eukliduv algoritmus\n");
	
	printf("a=");
	if (scanf("%u", &u) != 1)

	printf("b=");
	scanf("%u", &w);

	if (u,w != 2)
	{
		while (w != 0)
		{
			r = u % w;
			u = w;
			w = r;
		}
		printf("D čísel je: %u\n", u);
	}

	else 
	{
		printf("Chyba, spatne zadane cisla\n");
	}
	return 0;
}
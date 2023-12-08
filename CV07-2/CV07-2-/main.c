#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>


unsigned gcd(unsigned aU, unsigned aW)
{
	while (aW != 0)
	{
		unsigned r;
		r = aU % aW;
		aW = r;
	}
	return aU;
}

int main(void)
{
	unsigned u, w;
	printf("Eukliduv algoritmus\n");

	if (scanf("%u%u", &u, &w) != 2)
	{
		printf("Chyba - nebyla zadana dve cela cisla!\n");
		return 1;
	}

	printf("NSD: %u\n", gcd(u, w));


	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <ctype.h>

int main(void)
{
	double a, b, c;

	printf("Zadej koeficienty a b c:\n");
	
	printf("a=");
	scanf("%lf", &a);
	
	printf("b=");
	scanf("%lf", &b);

	printf("c=");
	scanf("%lf", &c);

	if (isalnum(a) && isalnum(b) && isalnum(c))
	{
		printf("Chyba cteni koeficientu a b c!\n");
		return 1;
	}
	double D = b * b - 4 * a * c;
	
	if (D >= 0) 
	{
		printf("\nKořeny jsou realne\n");
		D = sqrt(D);
		double x1 = -b + D;
		double x2 = -b - D;

		printf("x1 = %lf\n", x1);
		printf("x2 = %lf\n", x2);
	}
	else if(D < 0)
	{
		printf("\nKořeny jsou imaginární\n");
		D = sqrt(-D);
		double Re = -b / (2 * a);
		double Im = D / (2 * a);

		printf("x1 = %lf + j%lf\n", Re, Im);
		printf("x2 = %lf + j%lf\n", Re, Im);
	}
	else 
	{
		printf("Chyba pri vypoctu, restartuj program");
		return 2;
	}


	return 0;
}
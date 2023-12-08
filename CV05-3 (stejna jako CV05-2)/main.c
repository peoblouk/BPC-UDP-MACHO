#define _CRT_SECURE_NO_WARNINGS  // je zde jelikož funkce scanf je nebezpečná podle microsoft
#include <stdio.h>

double a, b;

double obvod(double sirka_, double vyska_)
{
	double obvod = 0;
	obvod = 2 * (sirka_ + vyska_);
	return obvod;
}

double obsah(double sirka_, double vyska_)
{
	double obsah = 0;
	obsah = sirka_ * vyska_;
	return obsah;
}

int main(void)
{
	char jednotka;

	printf("zadej jednotku= ");
	scanf("%s", jednotka);
	
	printf("zadej sirku= ");
	scanf("%lf", &a);

	printf("zadej vysku= ");
	scanf("%lf", &b);

	printf("obvod %lf %s\n", obvod(a, b), jednotka); // obvod
	printf("obsah %lf %s\n", obsah(a, b), jednotka); // obsah
}
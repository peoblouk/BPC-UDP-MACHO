#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <uchar.h>

// Funkce setlocale

int main(int argc, char* argv[])
{
	printf("%s\n", setlocale(LC_ALL, NULL)); // Všechny kategorie se nastaví na u US musí být 6.8 a CZ je 6,8
	printf("%lf\n", 3.14);

	printf("%s\n", setlocale(LC_ALL, "cs_CZ.UTF_8"));
	printf("%lf\n", 3.14);

	char text1[] = "České znaky i různé symboly ‰ ✉ ✆ ☺ ☕.";
	char text2[] = "České znaky i různé symboly \u2030 \u2709 \u2706 \u263A \u2615.";

	printf("%s\n", text1);
	printf("%s\n", text2);

	double x = 0;

	// sscanf("7.58", "%lf", &x); // Čte řetězec a převede ho do %lf
	//! parametry zadané na vstupu debugging jsou ve formě stringu, pro práci je nutno převést je podle formátovacího  
	sscanf(argv[2], "%lf", &x);

	printf("%lf\n", x);

	return 0;
}
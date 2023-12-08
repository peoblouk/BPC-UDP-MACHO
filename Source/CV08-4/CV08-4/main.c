#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>


// Inicializace datového typu TPoint
//1
struct TPoint {
	float iX;
	float iY;
};

//2
struct TRect 
{
	struct TPoint iPointLH;
	struct TPoint iPointRD;
};

int main(void)
{
	struct TRect rectangle= {
		.iPointLH = 
		{
			.iX=0, // bod osa x
			.iY=0	// bod osa y
		},
		.iPointRD = 
		{
			.iX=0,
			.iY=0
		}
	};
	printf("Zadej souradnice leveho horniho rohu:\n");
	if (scanf("%f %f", &rectangle.iPointLH.iX, &rectangle.iPointLH.iY) != 2)
	{
		printf("Chyba cteni");
		return 1;
	}

	printf("Zadej souradnice praveho rohu:\n");
	if (scanf("%f %f", &rectangle.iPointRD.iX, &rectangle.iPointRD.iY) != 2)
	{
		printf("Chyba cteni");
		return 1;
	}
	 // hypotf je odmocnina ze dvou clenu na druhou
	float l = hypotf(rectangle.iPointLH.iX - rectangle.iPointRD.iX, rectangle.iPointLH.iY - rectangle.iPointRD.iY);
	printf("Delka uhlopricky %f", l);
}
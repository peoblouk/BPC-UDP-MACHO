#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

// Inicializace datového typu Point
struct TPoint{
	float iX;
	float iY;
};


#if 0
float distance(float aX, float aY)
{
	float d;

	d = sqrtf((aX * aX) + (aY * aY));

	return d;
}
#endif


int main(void)
{
	// Definice proměnné point typu TPoint
	struct TPoint point =
	{
		.iX= 0,
		.iY= 0
	};

	printf("Tento program vypocita\n vzdálenost bodu od pocatku\n");

	if (scanf("%f %f", &point.iX, &point.iY) != 2)
	{
		printf("Spatne zadane parametry\n");
		return 1;
	}
	else
	{
		// printf("%f", distance(x, y));
		float r = sqrtf((point.iX * point.iY) + (point.iX * point.iY));
		printf("%f\n", r);
	}

	printf("%f %f", point.iX, point.iY);

	return 0;
}
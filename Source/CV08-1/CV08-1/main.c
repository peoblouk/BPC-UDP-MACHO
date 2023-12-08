#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>


float distance(float aX, float aY)
{
	float d;

	d = sqrtf((aX*aX ) + (aY*aY));

	return d;
}

int main(void)
{
	float x, y;
	printf("Tento program vypocita\n vzdálenost bodu od pocatku\n");

	if(scanf("%f %f", &x, &y) != 2)
	{
		printf("Spatne zadane parametry");
		return 1;
	}
	else
	{
		printf("%f", distance(x, y));
	}

	return 0;
}
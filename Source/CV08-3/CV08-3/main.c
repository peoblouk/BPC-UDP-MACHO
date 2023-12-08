#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

// #define DEBUG

// Inicializace datového typu TPoint
struct TPoint{
	float iX;
	float iY;
};

// Inicializace funkcí
struct TPoint read_point(void); // Čtení  (vrací TPoint)
float distance(struct TPoint aPoint); // Výpočet (vrací float)

int main(void)
{
	// Definice proměnné point typu TPoint
	struct TPoint point =
	{
		.iX = 0,
		.iY = 0
	};

	printf("Tento program vypocita\n vzdálenost bodu od pocatku\n");
	
	point = read_point();

	if ((point.iX == 0) && (point.iY == 0)) // Ověření, že funkce nemá hodnotu 0
	{
		printf("")
		return 1;
	}
	else
	{
		printf("%f", distance(point));
	}
	return 0;
}

struct TPoint read_point(void) // Čtení 
{
	struct TPoint point_fce;

	if (scanf("%f %f", &point_fce.iX, &point_fce.iY) != 2)
	{
		point_fce.iX, point_fce.iY = 0; // Ošetření vstupu
		printf("Spatne zadane promenne\n");
		#ifdef DEBUG
			printf("Error 1");
		#endif
	}
	else
	{
		return point_fce;
	}

}

float distance(struct TPoint aPoint)
{
	#ifdef DEBUG
		printf("%F\n", aPoint.iX);
		printf("%F\n", aPoint.iY);
	#endif

	return sqrtf((aPoint.iX * aPoint.iX) + (aPoint.iY * aPoint.iY));
}
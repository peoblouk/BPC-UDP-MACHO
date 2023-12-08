#include <stdio.h>

/* Paměťové místa, střídají adresu jelikož se má jednat o ochranu Windows, aby nebylo možné třeba Crack
   * je hondota proměnné a & je adresa proměnné kterou má v sobě pointer
*/

int main(void)
{
	int x = 10;
	int y = 20;

	int* ptr_x = NULL; // Inicializace pointeru
	int* ptr_y = NULL; // Inicializace pointeru
	
	ptr_x = &x;
	ptr_y = &y;

	printf("x= %d y=%d\n", x, y); // tisknu proměnnou
	printf("ptr_x=%p ptr_y=%p\n", ptr_x, ptr_y); // tisknu adresu kterou má v sobě pointer
	printf("Adresa x=%p Adresa y=%p\n", &x, &y); // tisknu adresu x a y
	printf("Adresa ptr_x=%p Adresa ptr_y=%p\n", &ptr_x, &ptr_y); // tisknu adresu v paměti, kterou má pointer

	/* // Výměna x za y 
	int tmp = x; // pomocná proměnná uložím zde hodnotu x
	x = y; 
	y = tmp;
	printf("Po vymene x=%d y=%d", x, y);*/


	// Výměna x za y za pomocí pointerů
	int tmp = *ptr_x; // vytvořím pomocnou proměnnou
	*ptr_x = *ptr_y;
	*ptr_y = tmp;
	printf("Po vymene x=%d , y=%d", x, y);

	return 0;
}
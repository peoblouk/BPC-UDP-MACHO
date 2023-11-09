#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdbool.h>
// #define DEBUG
bool flag_zero = 0;

// Inicializace datového typu TPoint
struct TPoint
{
    float iX;
    float iY;
};

// Inicializace datového typu TRect o dvou bodech XY
struct TRect
{
    struct TPoint iPointLH; // Levý horní roh
    struct TPoint iPointRD; // Pravý horní roh
};

struct TPoint read_point(void); // Čtení souřadnic X Y
struct TRect read_rect(void);   // Funkce čtení rohů
static inline float
diagonal(struct TRect rect_2); // Funkce pro výpočet délky diagonály

int main(void)
{
    struct TRect rectangle = {
        .iPointLH = {.iX = 0, .iY = 0},
        .iPointRD = {.iX = 0, .iY = 0}}; // Proměnná pro uložení výsledku
    rectangle = read_rect();             // Čtení od uživatele

    float l = diagonal(rectangle);
    printf("Delka uhlopricky %f", l);
}

struct TPoint read_point(void) //! Pouze se čtou body X Y
{
    struct TPoint point_fce;

    if (scanf("%f %f", &point_fce.iX, &point_fce.iY) != 2)
    {
        point_fce.iX, point_fce.iY = 0; // Ošetření vstupu
        flag_zero = 1;
    }
    else
    {
        flag_zero = 0;
        return point_fce;
    }
}

struct TRect read_rect(void) //! Funkce využívá read_point k přečtení dvou rohů
{
    struct TRect rect = {.iPointLH = {.iX = 0, .iY = 0},
                         .iPointRD = {.iX = 0, .iY = 0}}; // Pomocná proměnná
    printf("Zadej souradnice leveho horniho rohu (format X Y):\n");
    rect.iPointLH = read_point();
    if (flag_zero == 1)
    {
        rect.iPointLH.iX, rect.iPointLH.iY = 0;
        return rect;
    }
    else
    {
        printf("Zadej souradnice praveho rohu (format X Y):\n");
        rect.iPointLH = read_point();
        if (flag_zero == 1) // Vymaž proměnné  špatné čtení
        {
            rect.iPointLH.iX, rect.iPointLH.iY = 0;
            rect.iPointRD.iX, rect.iPointRD.iY = 0;
            return rect;
        }
        else
        {
            return rect;
        }
    }
}

static inline float diagonal(struct TRect rect_2) //! Funkce vypočítá diagonálu
{
    return hypotf(rect_2.iPointLH.iX - rect_2.iPointRD.iX,
                  rect_2.iPointLH.iY - rect_2.iPointRD.iY);
}
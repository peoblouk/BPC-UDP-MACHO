#ifndef TDATA_H
#define TDATA_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "check.h"

struct TData
{
	double* iPtr;
	size_t iNum;
};

int data_read(FILE* aFile, struct TData* aPtrData); // Funkce na �ten� vstupn�ch dat
int data_write(FILE* aFile, const struct TData aData); // Funkce na z�pis

int data_minmax(const struct TData aData, double* aPtrMin, double* aPtrMax);
int data_minmax_write(FILE* aFile, double aMin, double aMax);
void data_destroy(struct TData* aPtrData);

#endif // TDATA_h
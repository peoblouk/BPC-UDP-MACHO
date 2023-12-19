#ifndef TDATA_H
#define TDATA_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "check.h"// kontrola po alokaci 


struct TData { unsigned iID; char iDateStr[11]; float iValue; };

static inline int data_read(FILE* aFile, struct TData* aData)
{
	if (aFile == NULL || aData == NULL) // Kontrola předaných parametrů
	{
		return -1;
	}

	if (fscanf(aFile, "%u", &aData->iID) != 1) // Čtení iD
		return -2;

	if (fscanf(aFile, "%s", &aData->iDateStr) != 1) // Čtení řetězce string
		return -2;

	if (fscanf(aFile, "%f", &aData->iValue) != 1) // Čtení floatu
		return -2;

	// printf("{.iID=%u, .iDate = %s, .iValue =%f }\n", aData->iID, aData->iDateStr, aData->iValue); //debug

	return 0;
}


int data_mean(const size_t aNum, const struct TData aData[], float* aMeanPtr);

#endif // !TDATA_H

#include "TData.h"

int data_mean(const size_t aNum, const struct TData aData[], float* aMeanPtr)
{
	if (aNum == 0 || aMeanPtr == NULL)
	{
		return -1;
	}

	*aMeanPtr = 0;

	for (size_t i = 0; i < aNum; i++)
	{
		*aMeanPtr += (aData[i].iValue);
	}

	*aMeanPtr = (*aMeanPtr)/ aNum;

	printf("Mean Value: %f\n", *aMeanPtr);
	return 0;
}
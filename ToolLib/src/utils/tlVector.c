#include "utils/tlVector.h"
#include "utils/tlMemory.h"
#include "math/tlMathHelpers.h"

tlVector tlVecCreate(const void *pData, const int64_t length, const int64_t elementSize)
{
  tlVector newVector;
  newVector.pData = tlNewDynamicAlloc(length * elementSize);
	if (pData != NULL)
	  tlMemCopy(pData, length * elementSize, newVector.pData);
  newVector.elementSize = elementSize;
  newVector.size = length;
	newVector.capacity = length;

  return newVector;
}

tlVector tlVecCreateEmpty(const int64_t elementSize)
{
  tlVector newVector = tlVecCreate(NULL, 1, elementSize);
	newVector.capacity = 1;
	newVector.size = 0;
  return newVector;
}

tlVector tlVecCopy(const tlVector *pVector)
{
  tlVector newVector;
  newVector.pData = tlNewDynamicAlloc(pVector->elementSize * pVector->size);
  tlMemCopy(pVector->pData, pVector->elementSize * pVector->size, newVector.pData);
  newVector.elementSize = pVector->elementSize;
  newVector.size = pVector->size;
	newVector.capacity = pVector->capacity;
  return newVector;
}

void tlVecSwapIndex(tlVector *pVector, const int64_t indexA, const int64_t indexB)
{
	uint8_t temp[pVector->elementSize];
	void *ptrA = tlVecAt(pVector, indexA);
	void *ptrB = tlVecAt(pVector, indexB);

	tlMemCopy(ptrA, pVector->elementSize, temp);
	tlMemCopy(ptrB, pVector->elementSize, ptrA);
	tlMemCopy(temp, pVector->elementSize, ptrB);
	return;
}

void tlVecAppend(tlVector *pVector, void *pData)
{
	tlVecConcat(pVector, pData, 1);
}

tlVector tlVecSwap(tlVector **pVector)
{
  if (pVector == NULL || *pVector == NULL)
  {
    tlVector empty = {0};
    return empty;
  }

  tlVector newVector;
  newVector.pData = (*pVector)->pData;
  newVector.elementSize = (*pVector)->elementSize;
  newVector.size  = (*pVector)->size;
  tlFree((*pVector)->pData, (*pVector)->size * (*pVector)->elementSize, DYNAMIC);
  return newVector;
}

void tlVecRemove(tlVector *pVector, const int64_t index)
{
	for (int64_t element = index+1; element < pVector->size; ++element)
	{
		int64_t prevPosition = pVector->elementSize * element - 1;
		int64_t bytePosition = pVector->elementSize * element;
		*((uint8_t*)pVector->pData + prevPosition) = *((uint8_t*)pVector->pData + bytePosition);
	}
}

void tlVecClear(tlVector *pVector)
{
	tlFree(pVector->pData, pVector->elementSize * pVector->size, DYNAMIC);
	pVector->size = 0;
}

int64_t tlVecGetIndexOf(const tlVector *pVector, const void *pElement)
{
	for (int64_t index = 0; index < pVector->size; ++index)
		if (*(int8_t*)pElement == *(uint8_t*)pVector->pData + (index*pVector->elementSize))
			return index;

	return -1;
}

void *tlVecAt(tlVector *pVector, const int64_t index)
{
	if (pVector->pData == NULL)
		return NULL;

	if (index >= pVector->size)
		return NULL;

	return (uint8_t*)pVector->pData + (index * pVector->elementSize);
} 

// Sorter using bubble sort
tlVector tlVecSort(const tlVector *pVector, tlBool (*lambdaFunction)(const void *a, const void *b))
{
	int64_t index = 0;
	tlVector outputVector = *pVector;
	tlBool swapped = FALSE;
	for (int64_t i = 0; i < pVector->size; ++i)
	{
		for (int64_t j = 0; j < pVector->size - 1; ++j)
		{
			if (!lambdaFunction(
				tlVecAt(&outputVector, j),
				tlVecAt(&outputVector, j+1)))
			{
				tlVecSwapIndex(pVector, j, j+1);
				swapped = TRUE;
			}
		}

		if (swapped == FALSE)
		{
			break;
		}
	}

	return outputVector;
}

void tlVecJoin(tlVector *pInput, tlVector *pJoined, const tlBool freeOther)
{
	tlVecConcat(pInput, pJoined->pData, pJoined->elementSize * pJoined->size);
	if (freeOther)
		tlVecClear(pJoined);
}

void tlVecReserve(tlVector *pVector, const int64_t numElement)
{
	int64_t oldSizeBytes = pVector->elementSize * pVector->size;
	if (pVector->size > numElement)
		return;
  uint8_t* newAddress = tlDynamicAlloc(pVector->elementSize * numElement, 0);
  tlMemCopy(pVector->pData, pVector->elementSize * pVector->size, newAddress);
	tlFree(pVector->pData, oldSizeBytes, DYNAMIC);
	pVector->pData = newAddress;
	pVector->capacity = numElement;
}

void tlVecConcat(tlVector *pVector, const void *pData, int64_t length)
{
	int64_t oldSizeBytes = pVector->elementSize * pVector->size;
	int64_t newIndexSize = tlFloor(length / pVector->elementSize);
	if (pVector->capacity > pVector->size + newIndexSize)
	{
		// If the can hold it, then dont have to force reallocate
		tlMemCopy(pData, length, pVector->pData + oldSizeBytes);
		pVector->size += newIndexSize;
		return;
	}

	/// Create a new Address and write to taht
  uint8_t* newAddress = tlDynamicAlloc(oldSizeBytes + length, oldSizeBytes);
  tlMemCopy(pVector->pData, pVector->elementSize * pVector->size, newAddress);
	tlFree(pVector->pData, oldSizeBytes, DYNAMIC);
	tlMemCopy(pData, length, newAddress + oldSizeBytes);
	pVector->pData = newAddress;
	pVector->size += newIndexSize;
	pVector->capacity = pVector->size;
}




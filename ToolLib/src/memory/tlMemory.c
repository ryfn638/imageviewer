#include "utils/tlMemory.h"
#include "math/tlMathHelpers.h"
#include "math/tlDataTypes.h"

#include <Windows.h>
extern void* newAllocate(int64_t size);

tlMemoryManager staticManager;
tlMemoryManager dynamicManager;

void *CreateManagerArena(tlMemoryManager *pManager, int64_t size)
{
	pManager->pArena = newAllocate(tlMax(size, pManager->minSize));
	pManager->m_capacity = (BYTE_PAGE * tlCeil((float)size / BYTE_PAGE));
	pManager->m_arenaPosition = 0;
	return pManager->pArena;
}

void *CreateNewBucket(const int64_t size, tlMemoryManager *pManager)
{
  int64_t bucketIndex = tlLog2i(size);
	if ((1ULL << bucketIndex) < (uint64_t)size)
		bucketIndex++;

	int64_t bucketSize = tlPow(2, bucketIndex);
	bucketSize = tlMax(sizeof(tlMemBucket), bucketSize);

  if (NUM_SIZE_CLASSES <= bucketIndex)
    return NULL;
	
  if (pManager->m_pFreeHeads[bucketIndex] == NULL)
	{
		if (pManager->m_capacity < bucketSize)
		{
			CreateManagerArena(pManager, bucketSize);
		}
		uint8_t* newAddress = (uint8_t*)(pManager->pArena + pManager->m_arenaPosition);
		pManager->m_arenaPosition += bucketSize;
		pManager->m_capacity -= bucketSize;
		return newAddress;
	} else {
		tlMemBucket *block = pManager->m_pFreeHeads[bucketIndex];
		pManager->m_pFreeHeads[bucketIndex] = block->pBucket;
		return block;
	}
}

void *newAlloc(const int64_t size, tlMemoryManager *pManager)
{
	return CreateNewBucket(size, pManager);
}

void *tlStaticAlloc(const int64_t size)
{
	return newAlloc(size, &staticManager);
}

void *tlNewDynamicAlloc(const int64_t size)
{
	return tlDynamicAlloc(size, 0);
}

void *tlDynamicAlloc(const int64_t size, const int64_t previousSize)
{
	return newAlloc(tlMax(previousSize * DYNAMIC_SIZING, size), &dynamicManager);
}

void tlMemCopy(const void *pSource, const int64_t copySize, void *pDst)
{
	for (int i = 0; i < copySize; ++i)
		*(uint8_t*)(pDst + i) = *(uint8_t*)(pSource + i);
}

void FreeBucket(void *pData, const int64_t bucketIndex, tlMemoryManager *pManager)
{
	tlMemBucket *pBlock = pManager->m_pFreeHeads[bucketIndex];
	pManager->m_pFreeHeads[bucketIndex] = pData;
	pManager->m_pFreeHeads[bucketIndex]->pBucket = pBlock;
}

tlBool tlFree(void *pData, const int64_t size, const AllocationType type)
{
  int64_t bucketIndex = tlLog2i(size);
	if (!(type == DYNAMIC || type == STATIC))
		return FALSE;
	FreeBucket(pData, bucketIndex, (type == DYNAMIC) ? &dynamicManager : &staticManager);
	pData = NULL;
	return TRUE;
}
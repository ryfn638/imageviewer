#ifndef tlMemoryManager_h
#define tlMemoryManager_h

#include "math/tlDataTypes.h"
#define BYTE_PAGE 4096 // the amount of bytes per page when requesting memory
#define DYNAMIC_SIZING                                                         \
  2 // Every time a dynamic memory allocator runs out of room, up its allocation
    // by this multiplier
#define NUM_SIZE_CLASSES                                                       \
  16 // Allow up to 2^16 bytes. 1GB Max memory allocated at once

typedef enum { STATIC, DYNAMIC } AllocationType;
// Buckets
typedef struct tlMemBucket {
  struct tlMemBucket
      *pBucket; // Pointer to the next bucket. the next free bucket basically
} tlMemBucket;

typedef struct {
  tlMemBucket *m_pFreeHeads[NUM_SIZE_CLASSES];
  int64_t m_bucketCount;
  int64_t m_capacity;

  void *pArena; // Bump allocating parts of the new arena
  int64_t m_arenaPosition;
  int64_t m_arenaCapacity;
  int64_t minSize;
} tlMemoryManager;

extern tlMemoryManager staticManager;  // memory manager for static memory
extern tlMemoryManager dynamicManager; // memory manage for dynamic memory. All

void *CreateManagerArena(tlMemoryManager *pManager, int64_t size);
void *CreateNewBucket(const int64_t size, tlMemoryManager *pManager);
/// allocates memory and returns a pointer to it
///@param size the amount of data in bytes being allocated
///@param pManager the memory manager responsible. e.g. static or dynamic
///@param searchStreams if interested in searching existing streams for space.
///mainly for static
///@return void* the pointer to the new space in mem (hooray!)
void *newAlloc(const int64_t size, tlMemoryManager *pManager);

/// Allocator for static memory, tightly packs memory with no buffering
/// @param size memory in bytes to allocate
/// @return a ptr to the allocated memory
void *tlStaticAlloc(const int64_t size);

/// for Dynamic Allocations. Packs array room + a generous buffer for each
/// reallocation Best to reserve bytes in advance rather than call this
/// repetitively
/// @param size memory in bytes to allocate
/// @return a ptr to the allocated memory
void *tlNewDynamicAlloc(const int64_t size);
void *tlDynamicAlloc(const int64_t size, const int64_t previousSize);

/// memCopy. copies memory what can i say
///@param pSource the source of the copies memory
///@param pDst
///@param copyLength
void tlMemCopy(const void *pSource, const int64_t copySize, void *pDst);

// Comapres two locations in memory
// returns TRUE if all bytes are the same
// Decimal numbers may have some weierd logic
tlBool tlMemCompare(const void *pValueA, const void *pValueB,
                    const int64_t compSize);

tlBool tlFree(void *pData, const int64_t size, const AllocationType type);

#endif

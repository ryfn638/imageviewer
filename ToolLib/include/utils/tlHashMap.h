#ifndef tlHashMap_h
#define tlHashMap_h

#include "tlVector.h"

// Type declaration macro
#define DECL_TYPE(T) sizeof(T)

// Type definition for custom hash methods
typedef struct {
  uint64_t (*Hash)(void *pValue);
} tlHash;

// Creating a hash with the function pointer.
// You will have to ensure the function remains in scope
tlHash CreateHash(void (*Hash)(void *pValue));

// Default Hash Function
uint64_t DefaultHash(void *pValue);

// Default tlHash value
const tlHash defaultHash = {.Hash = &DefaultHash};

// Defininig tlHash Functions
#define TLHASH(T) (tlHash{.Hash = &(T)})

typedef struct {
  tlHash *pHashFunction;
  tlVector data; // Holds the size, Vectors of tlHashBucket
} tlHashMap;

/// Initialises a Hash Map
/// By default, initialises the hash function to the default hash function
/// You should hardly have to define your own hash function, but if need be
/// you can
tlHashMap InitHashMap(const size_t keySize, const size_t valueSize);

#define CreateHashMap(T, U) return InitHashMap(DECL_TYPE(T), DECL_TYPE(U));

void SetHashFunction(tlHashMap *pHashMap, tlHash *pHash);
void *GetValue(tlHashMap *pHashMap, void *pKey);
void Remove(tlHashMap *pHashMap, void *pKey);
void Clear(); // Frees the Hash Map

tlVector GetKeys(tlHashMap *pHashMap);
tlVector GetValues(tlHashMap *pHashMap);

#endif

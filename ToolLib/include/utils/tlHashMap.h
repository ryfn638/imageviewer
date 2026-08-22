#ifndef tlHashMap_h
#define tlHashMap_h

#include "tlVector.h"

// Type declaration macro
#define DECL_TYPE(T) sizeof(T)
typedef uint64_t (*HashFunc)(void *pValue);

// Default Hash Function
uint64_t DefaultHash(void *pValue);

// Technically dont need this.
// But its moreso to specify that it IS the hash function
#define DEFAULT_HASH &DefaultHash

typedef struct {
  HashFunc pHashFunction;
  tlVector data; // Holds the size, Vectors of tlHashBucket
  tlVector keys; // holds all the keys
} tlHashMap;

/// Initialises a Hash Map
/// By default, initialises the hash function to the default hash function
/// You should hardly have to define your own hash function, but if need be
/// you can
tlHashMap tlHMapInitHashMap(const int64_t valueSize);

// You can use the other macro, i just think this looks better for type
// definitions
// THIS HEAP ALLOCATES THE VECTOR. YOU WILL HAVE TO MANUALLY FREE IT
#define CreateHashMap(T, U) return InitHashMap(DECL_TYPE(T), DECL_TYPE(U));

// Assigns the Hash Function of the HashMap to a HashFunc
void tlHMapSetHashFunction(tlHashMap *pHashMap, HashFunc HashFunc);

// Make sure the the value *pkey is the same type as the keys
// Returns NULL should it fail
void *tlHMapGetValue(tlHashMap *pHashMap, void *pKey);

// Removes an Entry
tlBool tlHMapRemove(tlHashMap *pHashMap, void *pKey);
tlBool tlHMapRemoveValue(tlHashMap *pHashMap, void *pValue);

// This cannot do type checking, so ensure the types are important
// Tries to add, returns false if not added successfully
tlBool tlHMapTryAdd(tlHashMap *pHashMap, void *pKey, void *pValue);

// Same deal, ensure the right types are used
void tlHMapAddOrSet(tlHashMap *pHashMap, void *pKey, void *pValue);

// Clears and frees all the tlHashMap memory
void tlHMapClear(); // Frees the Hash Map

tlVector tlHMapGetKeys(tlHashMap *pHashMap);
tlVector tlHMapGetValues(tlHashMap *pHashMap);

#endif

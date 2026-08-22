#include "utils/tlHashMap.h"
#include "utils/tlMemory.h"

tlHashMap tlHMapInitHashMap(const int64_t valueSize) {
  tlHashMap newMap;
  newMap.data = tlVecCreateEmpty(valueSize);
  newMap.keys = tlVecCreateEmpty(sizeof(int64_t));
  tlHMapSetHashFunction(&newMap, DEFAULT_HASH);
  return newMap;
}

void tlHMapSetHashFunction(tlHashMap *pHashMap, HashFunc HashFunc) {
  pHashMap->pHashFunction = HashFunc;
}

void *tlHMapGetValue(tlHashMap *pHashMap, void *pKey) {
  if (!pHashMap || !pKey || pHashMap->data.capacity == 0 ||
      !pHashMap->pHashFunction)
    return NULL;

  int64_t index = pHashMap->pHashFunction(pKey) % pHashMap->data.capacity;

  void *pFoundKey = tlVecAt(&pHashMap->keys, index);
  if (pFoundKey != NULL &&
      tlMemCompare(pFoundKey, pKey, pHashMap->keys.elementSize))
    return tlVecAt(&pHashMap->data, index);

  for (int i = 0; i < pHashMap->keys.capacity; i++) {
    void *pMapKey = tlVecAt(&pHashMap->keys, i);
    if (pMapKey != NULL &&
        tlMemCompare(pMapKey, pKey, pHashMap->keys.elementSize)) {
      return tlVecAt(&pHashMap->data, index);
    }
  }

  return NULL;
}

// Implement these later, I want to do minecraft server thingymbabob
tlBool tlHMapRemove(tlHashMap *pHashMap, void *pKey) { return TRUE; }

tlBool tlHMapRemoveValue(tlHashMap *pHashMap, void *pValue) { return TRUE; }

tlBool tlHMapTryAdd(tlHashMap *pHashMap, void *pKey, void *pValue) {
  return TRUE;
}

void tlHMapAddOrSet(tlHashMap *pHashMap, void *pKey, void *pValue) {}

void tlHMapClear() {}

tlVector tlHMapGetKeys(tlHashMap *pHashMap) { return pHashMap->keys; }

tlVector tlHMapGetValues(tlHashMap *pHashMap) { return pHashMap->data; }

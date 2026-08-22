#include "math/tlDataTypes.h"
#define tlVector(T)

typedef struct
{
  int64_t memoryStreamIndex;
  int64_t size; // The amount of elements in the vector
	int64_t capacity; // The capacity of the vector
  void* pData; // Pointer to the beginning of a vector
  int64_t elementSize;
} tlVector;

// tlVector Constructor
tlVector tlVecCreate(const void *pData, const int64_t length, const int64_t elementSize);
tlVector tlVecCreateEmpty(const int64_t elementSize);
tlVector tlVecCopy(const tlVector *pVector);

/// Swaps Vector elements at indexes
///@param pVector 
///@param indexA 
///@param indexB 
void tlVecSwapIndex(tlVector *pVector, const int64_t indexA, const int64_t indexB);

/// AppendVector
/// Appends a singular value to a vector. For joining multiple, see concat
///@param pVector 
///@param pData 
void tlVecAppend(tlVector *pVector, void *pData);

/// ConcatVector, concatenates pointer on the the vector object
/// Assumes pData to be a stack allocated variable and therefore doesnt free it
/// @param pVector // The input vector
/// @param pData // pointer to the element being inputted
/// @param length // The amount of data being appeneded. By default 1
void tlVecConcat(tlVector *pVector, const void* pData, int64_t length);

/// tlVecReserve()
/// Reserves a vector with space, in other words puts the data into a different memory bucket.
/// TODO: Write error warnings to preven this from causing segmentation faults when running unguarded.
/// @param pVector 
/// @param numElement 
void tlVecReserve(tlVector *pVector, const int64_t numElement);

/// Remove()
/// removes data from a specific index, Assumes dataSize
/// @param pVector the vector being removed from
/// @param index the index that is getting removed
void tlVecRemove(tlVector *pVector, const int64_t index); 

/// ClearVector()
/// Clears the vector
/// @param pVector the vector being cleared
void tlVecClear(tlVector *pVector);

/// GetIndexOf()
/// Gets the Index of
int64_t tlVecGetIndexOf(const tlVector *pVector, const void *pElement);

/// AtIndex()
/// Returns the element at index
///@param pVector 
///@param index 
///@return void* 
///
void *tlVecAt(tlVector *pVector, const int64_t index);

/// SortVector()
/// Sorts a vector through defined lambda expressions
/// Assumes the correct Datatype used
/// @param pVector // The vector being sorted
/// @param lambdaFunction // The lambda function for comparisons
/// @return a sorted tlVector
tlVector tlVecSort(const tlVector *pVector, tlBool(*lambdaFunction)(const void* a, const void* b));

/// Joins Two Vectors
///@param inputVector 
///@param rhsVector 
///@param freeOther 
///
void tlVecJoin(tlVector *inputVector, tlVector *rhsVector, const tlBool freeOther);
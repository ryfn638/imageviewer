#ifndef tlMath_h
#define tlMath_h

#include "tlDataTypes.h"

#define TL_INTEGER_MASK 0xFF800000
#define TL_FRACTIONAL_MASK 0x007FFFFF

/// its floor
///@param data 
///@return int64_t 
int64_t tlFloor(float num);

/// its ceil what can i say
/// @param data 
/// @return 
int64_t tlCeil(float num);

/// its the larger number bro
///@param numA 
///@param numB 
///@return float big number
static inline float tlMax(float numA, float numB) {return (numA > numB) ? numA : numB; }

/// its the smaller number bro
///@param numA 
///@param numB 
///@return float small number
static inline float tlMin(float numA, float numB) {return (numA < numB) ? numA : numB; }

int64_t tlLog2i(const uint64_t num);

float tlPow(const float num, const int64_t power);

#endif

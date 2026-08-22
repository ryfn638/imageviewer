#include "math/tlDataTypes.h"
#include <windows.h>

#define FLOAT_DECIMAL_PLACES 6
#define NUM_CHAR_CONVERSION 48

void printformat(const char *string);

// Can use these generals, but for print normally use printFormat
void printChar(const char *string);
void printDecimal(const void* number, int64_t NUM_DECIMALS);
void printFloat(const float *number);
void printInt(const int64_t *number);
void printDouble(const double *number);

///
/// Unifies print char and print number using the same %s operations

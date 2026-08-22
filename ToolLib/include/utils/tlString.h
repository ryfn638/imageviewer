#include "utils/tlVector.h"

/// @brief tlStrings are just vector containers
/// main idea is to make it safer to make string vectors
/// which are always going to be chars if that makes sense
typedef struct
{
	tlVector data;
} tlString;

tlString tlCreateString(const char *stringData, const int64_t length);

void tlStringClear(const tlString *pString);
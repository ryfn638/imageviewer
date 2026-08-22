#include "utils/tlString.h"
#include "utils/tlMemory.h"

tlString tlCreateString(const char *stringData, const int64_t length)
{
	tlVector stringVector = tlVecCreate(stringData, length, sizeof(char));
	tlString newString;
	newString.data = stringVector;
	return newString;
}

void tlStringClear(const tlString *pString)
{
	tlVecClear(&pString->data);
}
#include <stdio.h>
#include "utils/tlVector.h"
#include "utils/tlMemory.h"
#include "io/stdout.h"

tlBool compare(const void* a, const void* b)
{
	return (*(const int*)a < *(const int*)b) ? TRUE : FALSE;
}

int main()
{
	printChar("abcbdajsjhdas \n");
	printf("Start Float Printing Vector \n");
	tlVector newVector = tlVecCreate((float[]){303.001f, 1.0f, 3.3321f, 4.231f}, 4, sizeof(float));
	for (int i = 0; i < 4; i++)
	{
		printFloat(*(float*)tlVecAt(&newVector, i));
		printChar("\n");
	}

	tlVecClear(&newVector);
	return 0;
}

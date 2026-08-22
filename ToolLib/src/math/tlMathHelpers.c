#include "math/tlMathHelpers.h"

// Doesnt work for negative floors. truncates -1.5 to -1. not -2
int64_t tlFloor(float num)
{
  return num;
}

int64_t tlCeil(float num)
{
	int64_t truncated = (int64_t)num;
	return (truncated < num) ? truncated + 1 : truncated;
}

int64_t tlLog2i(const uint64_t x)
{
  uint64_t returnValue = x;
  int64_t n = -1;
  while (returnValue) { returnValue >>= 1; n++;}
  return n;
}

float tlPow(const float num, const int64_t power)
{
	float product = 1;
	for (int64_t i = 0; i < power; i++)
	{
		product *= num;
	}
	return product;
}

#include "io/tlStdOut.h"
#include "float.h"
#include "math/tlMathHelpers.h"
#include "utils/tlVector.h"

extern void WriteStdOut(const char *string, int length);

void printChar(const char *string) {
  // searches for null terminated string
  int64_t length = 0;
  while (string[length] != '\0') {
    ++length;
  }

  WriteStdOut(string, length);
}

void printInt(const int64_t *number) {
  int64_t wholeNums = 0;
  // Whole Number handling
  {
    if (number <= 0)
      wholeNums++;

    int64_t num = *number;
    while (num > 0) {
      num /= 10;
      wholeNums++;
    }
  }

  tlVector printDigits = tlVecCreateEmpty(sizeof(const char));
  tlVecReserve(&printDigits, wholeNums);

  int64_t shiftedNumber = *number;
  for (int i = wholeNums - 1; i >= 0; --i) {
    int64_t multiplier = tlPow(10, i);
    int64_t divNumber = shiftedNumber;
    if (tlFloor(divNumber / multiplier) == 0) {
      divNumber = 0;
    } else {
      divNumber /= multiplier;
    }

    shiftedNumber -= divNumber * multiplier;

    char digitsChar = divNumber + NUM_CHAR_CONVERSION;
    tlVecAppend(&printDigits, &digitsChar);
  }

  WriteStdOut((const char *)printDigits.pData, printDigits.size);
  tlVecClear(&printDigits);
}

void printFloat(const float *number) { printDecimal(number, FLT_DIG); }

void printDouble(const double *number) { printDecimal(number, DBL_DIG); }

void printDecimal(const void *number, const int64_t NUM_DECIMALS) {
  // Prints the integer component

  float localFloat = *(const float *)number;
  int64_t flooredNum = (int64_t)localFloat;
  printInt(&flooredNum);

  const char dotPoint = '.';
  WriteStdOut(&dotPoint, 1);

  float shiftedNumber = (*(float *)number - flooredNum);

  int64_t wholeNums = 0;
  while (flooredNum > 0) {
    flooredNum /= 10;
    wholeNums++;
  }

  for (int64_t power = 1; power <= NUM_DECIMALS - wholeNums; ++power) {
    int8_t printedNum = (int8_t)(shiftedNumber * 10);
    char numChar = printedNum + NUM_CHAR_CONVERSION;
    WriteStdOut(&numChar, 1);
    shiftedNumber *= 10;
    shiftedNumber -= printedNum;
  }
}

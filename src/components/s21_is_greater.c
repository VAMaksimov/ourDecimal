#include "../s21_decimal.h"

bool s21_is_greater(s21_decimal a, s21_decimal b) {
  if (!isSetBit(a, MINUS_BIT_INDEX) && isSetBit(b, MINUS_BIT_INDEX)) {
    return true;
  }
  if (isSetBit(a, MINUS_BIT_INDEX) && !isSetBit(b, MINUS_BIT_INDEX)) {
    return false;
  }

  for (int i = ROW_NUMBER - 1; i >= 0; i--) {
    if (a.bits[i] > b.bits[i]) {
      return !isSetBit(a, MINUS_BIT_INDEX);
    } else if (a.bits[i] < b.bits[i]) {
      return isSetBit(a, MINUS_BIT_INDEX);
    }
  }
  return false;
}
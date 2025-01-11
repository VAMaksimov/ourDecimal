#include "../s21_decimal.h"

int s21_is_greater(s21_decimal a, s21_decimal b) {
  if (!isCorrectDecimal(&a) || !isCorrectDecimal(&b)) return false;

  bool result = false;
  int errorType = ADD_OK;
  bool negativeA = isSetBit(a, MINUS_BIT_INDEX);
  bool negativeB = isSetBit(b, MINUS_BIT_INDEX);

  alignScale(&a, &b, &errorType);
  if (errorType)
    result = false;
  else if (!negativeA && negativeB)
    result = true;
  else if (negativeA && !negativeB)
    result = false;

  else {
    for (int i = ROW_NUMBER - 2; i >= 0 && !result; i--) {
      if (a.bits[i] > b.bits[i])
        result = !negativeA;
      else if (a.bits[i] < b.bits[i])
        result = negativeA;
    }
  }
  return result;
}

int s21_is_equal(s21_decimal a, s21_decimal b) {
  if (!isCorrectDecimal(&a) || !isCorrectDecimal(&b)) return false;

  bool result = true;
  int errorType = ADD_OK;
  bool negativeA = isSetBit(a, MINUS_BIT_INDEX);
  bool negativeB = isSetBit(b, MINUS_BIT_INDEX);

  alignScale(&a, &b, &errorType);
  if (errorType)
    result = false;
  else if (negativeA != negativeB)
    result = false;
  else {
    for (int i = ROW_NUMBER - 2; i >= 0 && result; i--) {
      if (a.bits[i] != b.bits[i]) result = false;
    }
  }

  return result;
}

int s21_is_less(s21_decimal a, s21_decimal b) {
  return !s21_is_greater_or_equal(a, b);
}

int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  return !s21_is_equal(a, b);
}

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
  return s21_is_greater(a, b) || s21_is_equal(a, b);
}

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  return s21_is_less(a, b) || s21_is_equal(a, b);
}
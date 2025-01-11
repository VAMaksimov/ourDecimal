#include "../s21_decimal.h"

int s21_is_greater(s21_decimal a, s21_decimal b) {
  if (!isCorrectDecimal(&a) || !isCorrectDecimal(&b)) return false;

  bool result = false;
  int errorType = ADD_OK;
  bool negativeA = isSetBit(a, MINUS_BIT_INDEX);
  bool negativeB = isSetBit(b, MINUS_BIT_INDEX);

  if (!negativeA && negativeB) result = true;
  if (negativeA && !negativeB) result = false;

  alignScale(&a, &b, &errorType);
  if (errorType) result = false;

  for (int i = ROW_NUMBER - 1; i >= 0; i--) {
    if (a.bits[i] > b.bits[i])
      result = !negativeA;
    else if (a.bits[i] < b.bits[i])
      result = negativeA;
  }
  return result;
}

int s21_is_less(s21_decimal a, s21_decimal b) {
  if (!isCorrectDecimal(&a) || !isCorrectDecimal(&b)) return false;

  bool result = false;
  int errorType = ADD_OK;
  bool negativeA = isSetBit(a, MINUS_BIT_INDEX);
  bool negativeB = isSetBit(b, MINUS_BIT_INDEX);

  if (negativeA && !negativeB) result = true;
  if (!negativeA && negativeB) result = false;

  alignScale(&a, &b, &errorType);
  if (errorType) result = false;

  for (int i = ROW_NUMBER - 1; i >= 0; i--) {
    if (a.bits[i] < b.bits[i])
      result = !negativeA;
    else if (a.bits[i] > b.bits[i])
      result = negativeA;
  }
  return result;
}

int s21_is_equal(s21_decimal a, s21_decimal b) {
  if (!isCorrectDecimal(&a) || !isCorrectDecimal(&b)) return false;

  int errorType = ADD_OK;
  bool result = true;
  bool negativeA = isSetBit(a, MINUS_BIT_INDEX);
  bool negativeB = isSetBit(b, MINUS_BIT_INDEX);

  alignScale(&a, &b, &errorType);
  //   if (errorType) result = false;

  if (negativeA != negativeB) result = false;
  for (int i = ROW_NUMBER - 2; i >= 0 && result; i--) {
    if (a.bits[i] != b.bits[i]) result = false;
  }

  return true;
}

int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  return !s21_is_equal(a, b);
}

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
  return !s21_is_less(a, b);
}

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  return !s21_is_greater(a, b);
}
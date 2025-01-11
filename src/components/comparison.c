#include "../s21_decimal.h"

int s21_is_greater(s21_decimal a, s21_decimal b, int *errorType) {
  if (errorType == NULL) return false;

  bool negativeA = isSetBit(a, MINUS_BIT_INDEX);
  bool negativeB = isSetBit(b, MINUS_BIT_INDEX);

  if (!negativeA && negativeB) return true;
  if (negativeA && !negativeB) return false;

  alignScale(&a, &b, errorType);
  if (*errorType) return false;

  for (int i = ROW_NUMBER - 1; i >= 0; i--) {
    if (a.bits[i] > b.bits[i])
      return !negativeA;
    else if (a.bits[i] < b.bits[i])
      return negativeA;
  }
  return false;
}

int s21_is_less(s21_decimal a, s21_decimal b, int *errorType) {
  if (errorType == NULL) return false;

  bool negativeA = isSetBit(a, MINUS_BIT_INDEX);
  bool negativeB = isSetBit(b, MINUS_BIT_INDEX);

  if (negativeA && !negativeB) return true;
  if (!negativeA && negativeB) return false;

  alignScale(&a, &b, errorType);

  for (int i = ROW_NUMBER - 1; i >= 0; i--) {
    if (a.bits[i] < b.bits[i])
      return !negativeA;
    else if (a.bits[i] > b.bits[i])
      return negativeA;
  }
  return false;
}

int s21_is_equal(s21_decimal a, s21_decimal b, int *errorType) {
  if (errorType == NULL) return false;

  bool negativeA = isSetBit(a, MINUS_BIT_INDEX);
  bool negativeB = isSetBit(b, MINUS_BIT_INDEX);

  if (negativeA != negativeB) return false;

  alignScale(&a, &b, errorType);
  if (*errorType) return false;

  for (int i = ROW_NUMBER - 1; i >= 0; i--) {
    if (a.bits[i] != b.bits[i]) return false;
  }

  return true;
}

int s21_is_not_equal(s21_decimal a, s21_decimal b, int *errorType) {
  if (errorType == NULL) return false;

  bool negativeA = isSetBit(a, MINUS_BIT_INDEX);
  bool negativeB = isSetBit(b, MINUS_BIT_INDEX);

  if (negativeA != negativeB) return true;

  alignScale(&a, &b, errorType);
  if (*errorType) return false;

  for (int i = ROW_NUMBER - 1; i >= 0; i--) {
    if (a.bits[i] != b.bits[i]) return true;
  }

  return false;
}

int is_greater_or_equal(s21_decimal a, s21_decimal b, int *errorType) {
  if (errorType == NULL) return false;

  return s21_is_greater(a, b, errorType) || s21_is_equal(a, b, errorType);
}

int s21_is_less_or_equal(s21_decimal a, s21_decimal b, int *errorType) {
  if (errorType == NULL) return false;

  return s21_is_less(a, b, errorType) || s21_is_equal(a, b, errorType);
}
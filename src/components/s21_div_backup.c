#include "../s21_decimal.h"

int s21_div_another(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result) {
  if (result == NULL || !isCorrectDecimal(&value_1) ||
      !isCorrectDecimal(&value_2))
    return NUMBER_TOO_SMALL;
  if (isDecimalZero(value_2)) return DIVISION_BY_ZERO;

  int errorType = ADD_OK;
  resetDecimal(result);

  alignScale(&value_1, &value_2, &errorType);
  if (errorType != ADD_OK) return errorType;

  s21_decimal remainder = value_1, quotient = {0}, storage = {0};
  int n = 0;
  for (int i = VALUE_PART_SIZE - 1; i >= 0 && !isSetBit(value_1, i); i--) {
    n = i;
  }
  for (int i = VALUE_PART_SIZE - 1; i >= 0 && errorType == ADD_OK && n; i--) {
    shift_left(&remainder, 1, &errorType);
    shift_left(&storage, 1, &errorType);

    subtraction(storage, value_2, &storage, &errorType);

    // s21_decimal temp = storage;
    if (isSetBit(storage, MINUS_BIT_INDEX)) setBit(&remainder, 0);
    else addition(storage, value_2, &storage, &errorType);
    n--;
  }

  // Устанавливаем знак результата
  if (isSetBit(value_1, MINUS_BIT_INDEX) != isSetBit(value_2, MINUS_BIT_INDEX))
    setBit(&quotient, MINUS_BIT_INDEX);

  // Устанавливаем масштаб результата
  // setScale(&quotient, );

  // Копируем результат
  *result = quotient;

  return errorType;
}
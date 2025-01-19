#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (result == NULL || !isCorrectDecimal(&value)) return 1;
  int exp = getScale(value);
  int sign = isSetBit(value, MINUS_BIT_INDEX);
  *result = value;
  while (exp > 0) {
    div_10(result);
    exp--;
  }
  setScale(result, 0);
  if (sign) setBit(result, MINUS_BIT_INDEX);
  return 0;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (result == NULL || !isCorrectDecimal(&value)) return 1;
  *result = value;
  if (isSetBit(value, MINUS_BIT_INDEX)) {
    resetBit(result, MINUS_BIT_INDEX);
  } else {
    setBit(result, MINUS_BIT_INDEX);
  }
  return 0;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (result == NULL || !isCorrectDecimal(&value)) return 1;
  *result = value;
  int scale = getScale(value);
  if (scale > 0) {
    s21_decimal truncated = {0};
    s21_truncate(value, &truncated);
    s21_decimal fractional_part = {0};
    s21_sub(value, truncated, &fractional_part);
    if (isSetBit(value, MINUS_BIT_INDEX) && !isDecimalZero(fractional_part)) {
      s21_decimal one = {0};
      one.bits[0] = 1;
      s21_sub(truncated, one, result);
    } else {
      *result = truncated;
    }
  }
  return 0;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  if (result == NULL || !isCorrectDecimal(&value)) return 1;
  *result = value;
  int scale = getScale(value);
  if (scale > 0) {
    s21_decimal truncated = {0};
    s21_truncate(value, &truncated);

    s21_decimal fractional_part = {0};
    s21_sub(value, truncated, &fractional_part);

    resetBit(&fractional_part, MINUS_BIT_INDEX);

    s21_decimal half = {0};
    half.bits[0] = 5;
    setScale(&half, 1);

    // Диагностика
    // printDecimal(truncated);
    // printDecimal(fractional_part);  // Для отладки дробной части
    // printDecimal(half);  // Для отладки значения 0.5

    if (s21_is_greater_or_equal(fractional_part, half)) {
      s21_decimal one = {0};
      one.bits[0] = 1;

      if (!isSetBit(value, MINUS_BIT_INDEX)) {
        s21_add(truncated, one, result);
      } else {
        s21_sub(truncated, one,
                result);  // Для отрицательных чисел тоже добавляем
      }
    } else {
      *result = truncated;
    }
    setScale(result, 0);  // Устанавливаем масштаб результата в 0
  }
  return 0;
}

int div_10(s21_decimal *value) {
  long long int tmp = 0;
  int mod_10 = 0;
  for (int i = 2; i >= 0; i--) {
    tmp = mod_10 * pow(2, 32) + (unsigned)value->bits[i];
    mod_10 = tmp % 10;
    value->bits[i] = tmp / 10;
  }
  return mod_10;
}
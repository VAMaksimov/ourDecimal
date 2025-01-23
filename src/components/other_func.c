#include "../s21_decimal.h"

/**
 * @brief Truncates a decimal number to its integer part.
 *
 * If result is NULL or value is not a valid s21_decimal, the function
 * returns 1. Otherwise, it truncates value and stores the result in result, and
 * returns 0.
 *
 * @param value The number to be truncated.
 * @param result The address where the truncated number is stored.
 *
 * @return 0 if the truncation was successful, 1 otherwise.
 */
int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (result == NULL || !isCorrectDecimal(&value)) return 1;
  int exp = getScale(value);
  *result = value;
  while (exp > 0) {
    div_10(result);
    exp--;
  }
  setScale(result, 0);
  if (isSetBit(value, MINUS_BIT_INDEX)) setBit(result, MINUS_BIT_INDEX);
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

/**
 * @brief Floors a decimal number to the nearest integer not greater than the
 * original number.
 *
 * If result is NULL or value is not a valid s21_decimal, the function
 * returns 1. Otherwise, it calculates the floor of the value and stores the
 * result in result. The floor operation truncates the decimal number to its
 * integer part and, if the original number is negative and has a fractional
 * part, it decrements the integer part by 1 (Rounding towards negative
 * infinity).
 *
 * @param value The decimal number to be floored.
 * @param result The address where the floored number is stored.
 *
 * @return 0 if the floor operation was successful, 1 otherwise.
 */
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

/**
 * @brief Rounds a decimal number to the nearest integer.
 *
 * If result is NULL or value is not a valid s21_decimal, the function
 * returns 1. Otherwise, it calculates the round of the value and stores the
 * result in result. The round operation rounds the value to the nearest
 * integer. If the fractional part of the value is greater or equal to 0.5, the
 * result is incremented by 1. If the fractional part is less than 0.5, the
 * result is not changed.
 *
 * @param value The decimal number to be rounded.
 * @param result The address where the rounded number is stored.
 *
 * @return 0 if the round operation was successful, 1 otherwise.
 */
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

/**
 * @brief Divides a decimal number by 10.
 *
 * The loop iterates from the highest index (i = 2) down to the lowest (i
 * = 0).
 *
 * For each bits[i], the intermediate tmp value is formed by:
 * Shifting the previous remainder (mod_10) left by 32 bits (by multiplying
 * mod_10 with 2^32).
 * Adding the current 32-bit chunk (value->bits[i]) to that
 * accumulated value.
 * This effectively carries over any leftover remainder from
 * the previous iteration into the next higher-order 32-bit piece.
 *
 * Next, the code does: mod_10 = tmp % 10 → This finds the current remainder.
 * value->bits[i] = tmp / 10 → This updates bits[i] with the partial quotient.
 *
 * @param value A pointer to the decimal value to be divided by 10.
 *
 * @return The remainder of the division (mod_10).
 */
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

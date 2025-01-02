#include "../s21_decimal.h"

/**
 * @brief convert int to decimal
 * @param src int value
 * @param dst pointer to the decimal structure
 */
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == NULL) return CONVERTATION_ERROR;

  resetDecimal(dst);
  dst->bits[0] = abs(src);
  resetBit(dst, ADDITIONAL_INT_BIT);
  if (src < 0) setBit(dst, MINUS_BIT_INDEX);

  return CONVERTATION_SUCCESS;
}

/**
 * @brief converts decimal to int
 * @param src decimal value
 * @param dst pointer to the int structure
 */
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (dst == NULL || src.bits[1] || src.bits[2] ||
      isSetBit(src, ADDITIONAL_INT_BIT) || !isCorrectDecimal(&src))
    return CONVERTATION_ERROR;

  *dst = src.bits[0];
  if (isSetBit(src, MINUS_BIT_INDEX)) {
    *dst = ~(*dst) + 1;
    *dst |= (1 << 31);
  }
  return CONVERTATION_SUCCESS;
}

// int s21_from_float_to_decimal(float src, s21_decimal *dst) {
//   if (dst == NULL) return 1;

//   nullOutDecimal(dst);
// }

// int s21_from_decimal_to_float(s21_decimal src, float *dst) {}

#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == NULL) return 1;

  nullOut(dst);
  dst->bits[0] = abs(src);
  if (src < 0) setBit(dst, MINUS_BIT_INDEX);
  return 0;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (dst == NULL || src.bits[1] || src.bits[2] ||
      isSetBit(src, ADDITIONAL_INT_BIT))
    return 1;

  *dst = src.bits[0];
  if (isSetBit(src, MINUS_BIT_INDEX)) *dst = -(*dst);
  return 0;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (dst == NULL) return 1;

  nullOut(dst);
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {}

int main(void) {
  int number = __INT_MIN__;
  s21_decimal value;
  s21_from_int_to_decimal(number, &value);
  printf("%d", value.bits[0]);
  return 0;
}

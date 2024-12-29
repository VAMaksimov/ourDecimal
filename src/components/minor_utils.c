#include "../s21_decimal.h"

void nullOutDecimal(s21_decimal *dst) {
  int row = ROW_NUMBER;
  while (row--) dst->bits[row] = 0;
}

void nullOutLongDecimal(s21_long_decimal *dst) {
  int row = LONG_ROW_NUMBER;
  while (row--) dst->bits[row] = 0;
}

void negateDecimal(s21_decimal *dst) {
  int row = ROW_NUMBER;
  while (row--) dst->bits[row] = ~dst->bits[row] + 1;
}

bool isSetBit(s21_decimal dst, int index) {
  return (dst.bits[getRow(index)] & (1 << getColumn(index)));
}

void setBit(s21_decimal *dst, int index) {
  dst->bits[getRow(index)] |= (1 << getColumn(index));
}

void setLongBit(s21_long_decimal *dst, int index) {
  dst->bits[getRow(index)] |= (1 << getColumn(index));
}

void inverseBit(s21_decimal *dst, int index) {
  dst->bits[getRow(index)] ^= (1 << getColumn(index));
}

void resetBit(s21_decimal *dst, int index) {
  dst->bits[getRow(index)] &= ~((1 << getColumn(index)));
}

void resetLongBit(s21_long_decimal *dst, int index) {
  dst->bits[getRow(index)] &= ~((1 << getColumn(index)));
}

int get_scale(s21_decimal num) { return num.bits[3] >> 16; }

bool isCorrectDecimal(s21_decimal *num) {
  return num != NULL && get_scale(*num) <= 28 &&
         !(num->bits[3] & (0b01111111000000001111111111111111));
}

// bool s21_truncate(s21_decimal *value) {
//   if (result == NULL || !correct_decimal(&value)) return 1;
//   for (int i = 0; i < 3; i++) result->bits[i] = value.bits[i];
//   int exp = get_scale(value);
//   int sign = get_sign(value);
//   while (exp > 0) {
//     div_10(result);
//     exp--;
//   }
//   set_scale(result, 0);
//   set_sign(result, sign);
//   return 0;
// }
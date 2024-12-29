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

bool isSetLongBit(s21_long_decimal dst, int index) {
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

void alignScale(s21_decimal *value_1, s21_decimal *value_2, int *errorType) {
  int scale_1 = get_scale(*value_1), scale_2 = get_scale(*value_2);
  int scale_diff = scale_1 - scale_2;

  if (scale_diff > 0) {
    while (scale_diff--) multiply10(value_2, errorType);
  } else if (scale_diff < 0) {
    while (scale_diff++) multiply10(value_1, errorType);
  }
}

void multiply10(s21_decimal *src, int *errorType) {
  s21_decimal temp = *src;
  shift_left(src, 3, errorType);
  shift_left(&temp, 1, errorType);
  addition(*src, temp, src);
}

/*
number 1:
row\col | 3 | 2 | 1 | 0 |
-------------------------
0       | 0 | 0 | 0 | 1 |
1       | 0 | 0 | 0 | 0 |
2       | 0 | 0 | 0 | 0 |
*/
int shift_left(s21_decimal *src, int shift, int *errorType) {
  while (shift--) {
    if (isSetBit(*src, VALUE_PART_SIZE - 1)) {
      errorType = NUMBER_TOO_LARGE;
    } else {
      for (int bit_index = VALUE_PART_SIZE - 1; bit_index > 0; bit_index--) {
        if (isSetBit(*src, bit_index - 1)) {
          setBit(src, bit_index);
          resetBit(src, bit_index - 1);
        }
      }
      resetBit(src, 0);
    }
  }
}

// void longNormalization(s21_long_decimal *value_1, s21_long_decimal *value_2)
// {
//   int scale_1 = big_get_scale(*value_1);
//   int scale_2 = big_get_scale(*value_2);

//   if (scale_1 > scale_2) {
//     int scale_diff = scale_1 - scale_2;
//     for (int i = 0; i < scale_diff; i++) {
//       big_multiply_by_ten(value_2);
//     }
//   } else if (scale_2 > scale_1) {
//     int scale_diff = scale_2 - scale_1;
//     for (int i = 0; i < scale_diff; i++) {
//       big_multiply_by_ten(value_1);
//     }
//   }
// }

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
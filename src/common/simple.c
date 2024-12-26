#include "../s21_decimal.h"

void nullOut(s21_decimal *dst) {
  int row = ROW_NUMBER;
  while (row) dst->bits[--row] = 0;
}

bool isSetBit(s21_decimal dst, int index) {
  return (dst.bits[getRow(index)] & 1 << getColumn(index));
}

void setBit(s21_decimal *dst, int index) {
  dst->bits[getRow(index)] |= 1 << getColumn(index);
}

void inverseBit(s21_decimal *dst, int index) {
  dst->bits[getRow(index)] ^= 1 << getColumn(index);
}

void resetBit(s21_decimal *dst, int index) {
  dst->bits[getRow(index)] &= ~(1 << getColumn(index));
}

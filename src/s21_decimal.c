#include <stdio.h>

#define bool _Bool
#define true 1
#define false 0
#define MINUS_BIT (1 << 31)

#ifndef NULL
#define NULL ((void *)0)
#endif

#define abs(x) ((x) < 0 ? -(x) : (x))

typedef struct {
  int bits[4];
} s21_decimal;

void nullOut(s21_decimal *dst) {
  dst->bits[0] = 0;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  dst->bits[3] = 0;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == NULL) return 1;

  nullOut(dst);
  dst->bits[0] = abs(src);
  if (src < 0) dst->bits[3] |= MINUS_BIT;
  return 0;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  *dst = src.bits[0];
  bool negative = (src.bits[3] & (1 << 31)) ? true : false;
  if (negative) *dst = -(*dst);
}

int main(void) {
  int number = -__INT_MAX__;
  s21_decimal value;
  s21_from_int_to_decimal(number, &value);
  printf("%d", value.bits[0]);
  return 0;
}

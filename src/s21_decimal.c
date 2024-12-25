typedef struct {
  int bits[4];
} s21_decimal;

#include <stdbool.h>

#define bool _Bool
#define true 1
#define false 0
#define NULL ((void *)0)

#define abs(x) ((x) < 0 ? -(x) : (x))

void nullOut(s21_decimal *dst) {
  dst->bits[0] = 0;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  dst->bits[3] = 0;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == NULL) return 1;

  nullOut(dst);

  if (src == -__INT_MAX__) {
    dst->bits[0] = __INT_MAX__;
    dst->bits[3] |= (1 << 31);
  } else {
    bool negative = (src < 0) ? true : false;
    int value = (negative) ? -src : src;
    dst->bits[0] = value;
    if (negative) dst->bits[3] |= (1 << 31);
  }
  return 0;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  *dst = src.bits[0];
  bool negative = (src.bits[3] & (1 << 31)) ? true : false;
  if (negative) *dst = -(*dst);
}

int main(void) {
  int number = 0;
  s21_decimal value;
  s21_from_int_to_decimal(number, &value);
  return 0;
}

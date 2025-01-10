#include <stdio.h>

#include "s21_decimal.h"

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  int result = 0;
  short a_sign_bit = (a.bits[3] & (1 << 31)) >> 31;
  short b_sign_bit = (b.bits[3] & (1 << 31)) >> 31;
  short mantisa_a[MANTISA_LONG], mantisa_b[MANTISA_LONG];
  s21_init_mantisa(&a, mantisa_a);
  s21_init_mantisa(&b, mantisa_b);
  if (a_sign_bit != b_sign_bit) {
    result = a_sign_bit > b_sign_bit;

    if (s21_is_null_mantisa(mantisa_a) && s21_is_null_mantisa(mantisa_b)) {
      result = 1;
    }

  } else {
    int scale_a = (a.bits[3] & SCALE) >> 16;
    int scale_b = (b.bits[3] & SCALE) >> 16;

    // printf("\nBefore:\n1)");
    // for (int i = 0; i < MANTISA_LONG; i++) {
    //     printf("%d ", mantisa_a[i]);
    // }
    // printf("\n\n2)");
    // for (int i = 0; i < MANTISA_LONG; i++) {
    //     printf("%d ", mantisa_b[i]);
    // }

    s21_normalize_decimal(mantisa_a, mantisa_b, scale_a - scale_b);

    // printf("\n\nAfter:\n1)");
    // for (int i = 0; i < MANTISA_LONG; i++) {
    //     printf("%d ", mantisa_a[i]);
    // }
    // printf("\n\n2)");
    // for (int i = 0; i < MANTISA_LONG; i++) {
    //     printf("%d ", mantisa_b[i]);
    // }
    // printf("\n");

    int cmp = s21_compare_mantiss(mantisa_a, mantisa_b);

    if (a_sign_bit == 0) {
      result = cmp <= 0;
    } else {
      result = cmp >= 0;
    }
  }

  return result;
}

int s21_is_greater(s21_decimal a, s21_decimal b) {
  return !(s21_is_less_or_equal(a, b));
}

int s21_is_less(s21_decimal a, s21_decimal b) { return s21_is_greater(b, a); }

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
  return s21_is_less_or_equal(b, a);
}

int s21_is_equal(s21_decimal a, s21_decimal b) {
  return ((s21_is_less_or_equal(a, b) && s21_is_less_or_equal(b, a)));
}

int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  return !(s21_is_equal(a, b));
}

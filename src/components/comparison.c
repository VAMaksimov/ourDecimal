#include <stdio.h>
#include "s21_decimal.h"

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
    short a_sign_bit = (short)((a.bits[3] >> 31) & 1);
    short b_sign_bit = (short)((b.bits[3] >> 31) & 1);

    short mantisa_a[MANTISA_LONG], mantisa_b[MANTISA_LONG];
    s21_init_mantisa(&a, mantisa_a);
    s21_init_mantisa(&b, mantisa_b);

    if (a_sign_bit != b_sign_bit) {
        if (s21_is_null_mantisa(mantisa_a) && s21_is_null_mantisa(mantisa_b)) {
            return 1;
        }
        return a_sign_bit > b_sign_bit;
    }

    int scale_diff = ((a.bits[3] & SCALE) >> 16) - ((b.bits[3] & SCALE) >> 16);
    s21_normalize_decimal(mantisa_a, mantisa_b, scale_diff);

    int cmp = s21_compare_mantiss(mantisa_a, mantisa_b);
    return a_sign_bit ? cmp >= 0 : cmp <= 0;
}

int s21_is_greater(s21_decimal a, s21_decimal b) {
    return !s21_is_less_or_equal(a, b);
}

int s21_is_less(s21_decimal a, s21_decimal b) {
    return !s21_is_greater_or_equal(a, b);
}

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
    return !s21_is_less(a, b);
}

int s21_is_equal(s21_decimal a, s21_decimal b) {
    short mantisa_a[MANTISA_LONG], mantisa_b[MANTISA_LONG];
    s21_init_mantisa(&a, mantisa_a);
    s21_init_mantisa(&b, mantisa_b);

    int scale_diff = ((a.bits[3] & SCALE) >> 16) - ((b.bits[3] & SCALE) >> 16);
    s21_normalize_decimal(mantisa_a, mantisa_b, scale_diff);

    return (s21_compare_mantiss(mantisa_a, mantisa_b) == 0) &&
           ((a.bits[3] & (1 << 31)) == (b.bits[3] & (1 << 31)));
}

int s21_is_not_equal(s21_decimal a, s21_decimal b) {
    return !s21_is_equal(a, b);
}


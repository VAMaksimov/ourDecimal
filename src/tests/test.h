#ifndef TEST_H
#define TEST_H

#include <check.h>
#include <stdio.h>

#include "../s21_decimal.h"

#define __DECIMAL_FULL_ROW__ 0xffffffff
#define __DECIMAL_LOWER_MIDPOINT__ 0x7fffffff
#define __DECIMAL_UPPER_MIDPOINT__ 0x80000000
#define __DECIMAL_NEGATIVE_INT_INFO__ 0x80000000
#define __DECIMAL_POSITIVE_INT_INFO__ 0x00000000

void assertDecimal(s21_decimal expected, s21_decimal actual);
void assertLongDecimal(s21_long_decimal expected, s21_long_decimal actual);
Suite *convert_suite(void);
Suite *arithmetic_suite(void);

#endif  // TEST_H
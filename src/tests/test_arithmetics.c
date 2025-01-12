#include "test.h"

void performMultiplication(s21_decimal subject1, s21_decimal subject2,
                           s21_decimal expected, s21_decimal *actual,
                           int errorType) {
  int result = s21_mul(subject1, subject2, actual);
  assertDecimal(expected, *actual);
  ck_assert_int_eq(result, errorType);
}

void performAddition(s21_decimal subject1, s21_decimal subject2,
                     s21_decimal expected, s21_decimal *actual, int errorType) {
  int result = s21_add(subject1, subject2, actual);
  assertDecimal(expected, *actual);
  ck_assert_int_eq(result, errorType);
}

void performSubtraction(s21_decimal subject1, s21_decimal subject2,
                        s21_decimal expected, s21_decimal *actual,
                        int errorType) {
  int result = s21_sub(subject1, subject2, actual);
  assertDecimal(expected, *actual);
  ck_assert_int_eq(result, errorType);
}

/* s21_add */

START_TEST(add_standard_1) {
  s21_decimal subject1 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual, expected = {{2, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  performAddition(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

START_TEST(add_standard_2) {
  s21_decimal subject1 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{0, 1, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual, expected = {{1, 1, 0, __DECIMAL_POSITIVE_INT_INFO__}};

  performAddition(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

START_TEST(add_standard_3) {
  s21_decimal subject1 = {{25, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{75, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual, expected = {{100, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};

  performAddition(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

START_TEST(add_standard_4) {
  s21_decimal subject1 = {{__DECIMAL_FULL_ROW__, 0, 0,
                           __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual, expected = {{0, 1, 0, __DECIMAL_POSITIVE_INT_INFO__}};

  performAddition(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

START_TEST(add_standard_5) {
  s21_decimal subject1 = {{__DECIMAL_FULL_ROW__, 0, 0,
                           __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {
                  {__DECIMAL_FULL_ROW__, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual, expected = {{__DECIMAL_FULL_ROW__ - 1, 1, 0,
                                   __DECIMAL_POSITIVE_INT_INFO__}};

  performAddition(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

START_TEST(add_standard_6) {
  s21_decimal subject1 = {{25, 0, 0, __POSITIVE_AND_SCALE_EQUALS_1__}},
              subject2 = {{75, 0, 0, __POSITIVE_AND_SCALE_EQUALS_1__}};
  s21_decimal actual, expected = {{100, 0, 0, __POSITIVE_AND_SCALE_EQUALS_1__}};

  performAddition(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

START_TEST(add_standard_7) {
  s21_decimal subject1 = {{__DECIMAL_FULL_ROW__, 0, 0,
                           __POSITIVE_AND_SCALE_EQUALS_8__}},
              subject2 = {{1, 0, 0, __POSITIVE_AND_SCALE_EQUALS_8__}};
  s21_decimal actual, expected = {{0, 1, 0, __POSITIVE_AND_SCALE_EQUALS_8__}};

  performAddition(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

START_TEST(add_standard_8) {
  s21_decimal subject1 = {{__DECIMAL_FULL_ROW__, 0, 0,
                           __POSITIVE_AND_SCALE_EQUALS_1__}},
              subject2 = {{1, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_1__}};
  s21_decimal actual, expected = {{__DECIMAL_FULL_ROW__ - 1, 0, 0,
                                   __POSITIVE_AND_SCALE_EQUALS_1__}};

  performAddition(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

START_TEST(add_standard_9) {
  s21_decimal subject1 = {{25, 0, 0, __POSITIVE_AND_SCALE_EQUALS_1__}},
              subject2 = {{75, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_1__}};
  s21_decimal actual, expected = {{50, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_1__}};

  performAddition(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

START_TEST(add_standard_10) {
  s21_decimal subject1 = {{25, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_8__}},
              subject2 = {{75, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_8__}};
  s21_decimal actual, expected = {{100, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_8__}};

  performAddition(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

START_TEST(add_standard_11) {
  s21_decimal subject1 = {{2, 0, 0, __POSITIVE_AND_SCALE_EQUALS_1__}},
              subject2 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual, expected = {{12, 0, 0, __POSITIVE_AND_SCALE_EQUALS_1__}};

  performAddition(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

START_TEST(add_standard_12) {
  s21_decimal subject1 = {{0, 0, 0, __POSITIVE_AND_SCALE_EQUALS_8__}},
              subject2 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual,
      expected = {{100000000, 0, 0, __POSITIVE_AND_SCALE_EQUALS_8__}};

  performAddition(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

START_TEST(add_standard_13) {
  s21_decimal subject1 = {{1, 0, 0, __POSITIVE_AND_SCALE_EQUALS_8__}},
              subject2 = {{1, 0, 0, __DECIMAL_NEGATIVE_INT_INFO__}};
  s21_decimal actual,
      expected = {{99999999, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_8__}};

  performAddition(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

START_TEST(add_standard_14) {
  s21_decimal subject1 = {{0, 0, __DECIMAL_FULL_ROW__,
                           __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{1, 0, 0, __DECIMAL_NEGATIVE_INT_INFO__}};
  s21_decimal actual,
      expected = {{__DECIMAL_FULL_ROW__, __DECIMAL_FULL_ROW__,
                   __DECIMAL_FULL_ROW__ - 1, __DECIMAL_POSITIVE_INT_INFO__}};

  performAddition(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

START_TEST(add_border_1) {
  s21_decimal subject1 = {{__DECIMAL_FULL_ROW__, __DECIMAL_FULL_ROW__,
                           __DECIMAL_FULL_ROW__,
                           __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual = {0}, expected = {0};
  performAddition(subject1, subject2, expected, &actual, NUMBER_TOO_LARGE);
}
END_TEST

START_TEST(add_border_2) {
  s21_decimal subject1 = {{__DECIMAL_FULL_ROW__, __DECIMAL_FULL_ROW__,
                           __DECIMAL_FULL_ROW__,
                           __DECIMAL_NEGATIVE_INT_INFO__}},
              subject2 = {
                  {__DECIMAL_FULL_ROW__, 0, 0, __DECIMAL_NEGATIVE_INT_INFO__}};
  s21_decimal actual = {0}, expected = {0};
  performAddition(subject1, subject2, expected, &actual, NUMBER_TOO_SMALL);
}
END_TEST

START_TEST(add_border_3) {
  s21_decimal subject1 = {{0, __DECIMAL_FULL_ROW__, __DECIMAL_FULL_ROW__,
                           __DECIMAL_NEGATIVE_INT_INFO__}},
              subject2 = {{__DECIMAL_FULL_ROW__, 0, 0, __SCALE_IS_TOO_BIG__}};
  s21_decimal actual = {0}, expected = {0};
  performAddition(subject1, subject2, expected, &actual, NUMBER_TOO_SMALL);
}
END_TEST

START_TEST(add_border_4) {
  s21_decimal subject1 = {{0, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{__DECIMAL_FULL_ROW__, __DECIMAL_FULL_ROW__,
                           __DECIMAL_FULL_ROW__,
                           __DECIMAL_NEGATIVE_INT_INFO__}};
  s21_decimal actual,
      expected = {{__DECIMAL_FULL_ROW__, __DECIMAL_FULL_ROW__,
                   __DECIMAL_FULL_ROW__, __DECIMAL_NEGATIVE_INT_INFO__}};
  performAddition(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

/* s21_sub */

START_TEST(sub_standard_1) {
  s21_decimal subject1 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual, expectedSub = {{0, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  performSubtraction(subject1, subject2, expectedSub, &actual, ADD_OK);
}
END_TEST

START_TEST(sub_standard_2) {
  s21_decimal subject1 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{0, 1, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual, expectedSub = {{__DECIMAL_FULL_ROW__, 0, 0,
                                      __DECIMAL_NEGATIVE_INT_INFO__}};

  performSubtraction(subject1, subject2, expectedSub, &actual, ADD_OK);
}
END_TEST

START_TEST(sub_standard_3) {
  s21_decimal subject1 = {{25, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{75, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual, expectedSub = {{50, 0, 0, __DECIMAL_NEGATIVE_INT_INFO__}};

  performSubtraction(subject1, subject2, expectedSub, &actual, ADD_OK);
}
END_TEST

START_TEST(sub_standard_4) {
  s21_decimal subject1 = {{__DECIMAL_FULL_ROW__, 0, 0,
                           __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual, expectedSub = {{__DECIMAL_FULL_ROW__ - 1, 0, 0,
                                      __DECIMAL_POSITIVE_INT_INFO__}};

  performSubtraction(subject1, subject2, expectedSub, &actual, ADD_OK);
}
END_TEST

START_TEST(sub_standard_5) {
  s21_decimal subject1 = {{__DECIMAL_FULL_ROW__, 0, 0,
                           __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {
                  {__DECIMAL_FULL_ROW__, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual, expectedSub = {{0, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};

  performSubtraction(subject1, subject2, expectedSub, &actual, ADD_OK);
}
END_TEST

START_TEST(sub_standard_6) {
  s21_decimal subject1 = {{25, 0, 0, __POSITIVE_AND_SCALE_EQUALS_1__}},
              subject2 = {{75, 0, 0, __POSITIVE_AND_SCALE_EQUALS_1__}};
  s21_decimal actual,
      expectedSub = {{50, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_1__}};

  performSubtraction(subject1, subject2, expectedSub, &actual, ADD_OK);
}
END_TEST

START_TEST(sub_standard_7) {
  s21_decimal subject1 = {{__DECIMAL_FULL_ROW__, 0, 0,
                           __POSITIVE_AND_SCALE_EQUALS_8__}},
              subject2 = {{1, 0, 0, __POSITIVE_AND_SCALE_EQUALS_8__}};
  s21_decimal actual, expectedSub = {{__DECIMAL_FULL_ROW__ - 1, 0, 0,
                                      __POSITIVE_AND_SCALE_EQUALS_8__}};

  performSubtraction(subject1, subject2, expectedSub, &actual, ADD_OK);
}
END_TEST

START_TEST(sub_standard_8) {
  s21_decimal subject1 = {{__DECIMAL_FULL_ROW__, 0, 0,
                           __POSITIVE_AND_SCALE_EQUALS_1__}},
              subject2 = {{1, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_1__}};
  s21_decimal actual,
      expectedSub = {{0, 1, 0, __POSITIVE_AND_SCALE_EQUALS_1__}};

  performSubtraction(subject1, subject2, expectedSub, &actual, ADD_OK);
}
END_TEST

START_TEST(sub_standard_9) {
  s21_decimal subject1 = {{25, 0, 0, __POSITIVE_AND_SCALE_EQUALS_1__}},
              subject2 = {{75, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_1__}};
  s21_decimal actual,
      expectedSub = {{100, 0, 0, __POSITIVE_AND_SCALE_EQUALS_1__}};

  performSubtraction(subject1, subject2, expectedSub, &actual, ADD_OK);
}
END_TEST

START_TEST(sub_standard_10) {
  s21_decimal subject1 = {{25, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_8__}},
              subject2 = {{75, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_8__}};
  s21_decimal actual,
      expectedSub = {{50, 0, 0, __POSITIVE_AND_SCALE_EQUALS_8__}};

  performSubtraction(subject1, subject2, expectedSub, &actual, ADD_OK);
}
END_TEST

START_TEST(sub_standard_11) {
  s21_decimal subject1 = {{2, 0, 0, __POSITIVE_AND_SCALE_EQUALS_1__}},
              subject2 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual,
      expectedSub = {{8, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_1__}};

  performSubtraction(subject1, subject2, expectedSub, &actual, ADD_OK);
}
END_TEST

START_TEST(sub_standard_12) {
  s21_decimal subject1 = {{0, 0, 0, __POSITIVE_AND_SCALE_EQUALS_8__}},
              subject2 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual,
      expectedSub = {{100000000, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_8__}};

  performSubtraction(subject1, subject2, expectedSub, &actual, ADD_OK);
}
END_TEST

START_TEST(sub_standard_13) {
  s21_decimal subject1 = {{1, 0, 0, __POSITIVE_AND_SCALE_EQUALS_8__}},
              subject2 = {{1, 0, 0, __DECIMAL_NEGATIVE_INT_INFO__}};
  s21_decimal actual,
      expectedSub = {{100000001, 0, 0, __POSITIVE_AND_SCALE_EQUALS_8__}};

  performSubtraction(subject1, subject2, expectedSub, &actual, ADD_OK);
}
END_TEST

START_TEST(sub_standard_14) {
  s21_decimal subject1 = {{0, 0, __DECIMAL_FULL_ROW__,
                           __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{1, 0, 0, __DECIMAL_NEGATIVE_INT_INFO__}};
  s21_decimal actual, expectedSub = {{1, 0, __DECIMAL_FULL_ROW__,
                                      __DECIMAL_POSITIVE_INT_INFO__}};

  performSubtraction(subject1, subject2, expectedSub, &actual, ADD_OK);
}
END_TEST

START_TEST(sub_border_1) {
  s21_decimal subject1 = {{__DECIMAL_FULL_ROW__, __DECIMAL_FULL_ROW__,
                           __DECIMAL_FULL_ROW__,
                           __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{1, 0, 0, __DECIMAL_NEGATIVE_INT_INFO__}};
  s21_decimal actual = {0}, expected = {0};
  performSubtraction(subject1, subject2, expected, &actual, NUMBER_TOO_LARGE);
}
END_TEST

START_TEST(sub_border_2) {
  s21_decimal subject1 = {{__DECIMAL_FULL_ROW__, __DECIMAL_FULL_ROW__,
                           __DECIMAL_FULL_ROW__,
                           __DECIMAL_NEGATIVE_INT_INFO__}},
              subject2 = {
                  {__DECIMAL_FULL_ROW__, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual = {0}, expected = {0};
  performSubtraction(subject1, subject2, expected, &actual, NUMBER_TOO_SMALL);
}
END_TEST

START_TEST(sub_border_3) {
  s21_decimal subject1 = {{0, __DECIMAL_FULL_ROW__, __DECIMAL_FULL_ROW__,
                           __DECIMAL_NEGATIVE_INT_INFO__}},
              subject2 = {{__DECIMAL_FULL_ROW__, 0, 0, __SCALE_IS_TOO_BIG__}};
  s21_decimal actual = {0}, expected = {0};
  performSubtraction(subject1, subject2, expected, &actual, NUMBER_TOO_SMALL);
}
END_TEST

START_TEST(sub_border_4) {
  s21_decimal subject1 = {{0, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{__DECIMAL_FULL_ROW__, __DECIMAL_FULL_ROW__,
                           __DECIMAL_FULL_ROW__,
                           __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual,
      expected = {{__DECIMAL_FULL_ROW__, __DECIMAL_FULL_ROW__,
                   __DECIMAL_FULL_ROW__, __DECIMAL_NEGATIVE_INT_INFO__}};
  performSubtraction(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

/* s21_mul */

START_TEST(mul_standard_1) {
  s21_decimal subject1 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual, expected = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  performMultiplication(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

START_TEST(mul_standard_2) {
  s21_decimal subject1 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{0, 1, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual, expected = {{0, 1, 0, __DECIMAL_POSITIVE_INT_INFO__}};

  performMultiplication(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

START_TEST(mul_standard_3) {
  s21_decimal subject1 = {{5, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{12, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual, expected = {{60, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};

  performMultiplication(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

START_TEST(mul_standard_4) {
  s21_decimal subject1 = {{__DECIMAL_FULL_ROW__, 0, 0,
                           __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual,
      expected = {{__DECIMAL_FULL_ROW__, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};

  performMultiplication(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

START_TEST(mul_standard_5) {
  s21_decimal subject1 = {{__DECIMAL_FULL_ROW__, 0, 0,
                           __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{2, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual, expected = {{__DECIMAL_FULL_ROW__ - 1, 1, 0,
                                   __DECIMAL_POSITIVE_INT_INFO__}};

  performMultiplication(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

START_TEST(mul_standard_6) {
  s21_decimal subject1 = {{12, 0, 0, __POSITIVE_AND_SCALE_EQUALS_1__}},
              subject2 = {{5, 0, 0, __POSITIVE_AND_SCALE_EQUALS_1__}};
  s21_decimal actual, expected = {{60, 0, 0, __POSITIVE_AND_SCALE_EQUALS_2__}};

  performMultiplication(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

START_TEST(mul_standard_7) {
  s21_decimal subject1 = {{__DECIMAL_FULL_ROW__, 0, 0,
                           __POSITIVE_AND_SCALE_EQUALS_8__}},
              subject2 = {{1, 0, 0, __POSITIVE_AND_SCALE_EQUALS_8__}};
  s21_decimal actual, expected = {{__DECIMAL_FULL_ROW__, 0, 0,
                                   __POSITIVE_AND_SCALE_EQUALS_16__}};

  performMultiplication(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

START_TEST(mul_standard_8) {
  s21_decimal subject1 = {{__DECIMAL_FULL_ROW__, 0, 0,
                           __POSITIVE_AND_SCALE_EQUALS_1__}},
              subject2 = {{1, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_1__}};
  s21_decimal actual, expected = {{__DECIMAL_FULL_ROW__, 0, 0,
                                   __NEGATIVE_AND_SCALE_EQUALS_2__}};

  performMultiplication(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

START_TEST(mul_standard_9) {
  s21_decimal subject1 = {{5, 0, 0, __POSITIVE_AND_SCALE_EQUALS_1__}},
              subject2 = {{12, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_1__}};
  s21_decimal actual, expected = {{60, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_2__}};

  performMultiplication(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

START_TEST(mul_standard_10) {
  s21_decimal subject1 = {{5, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_8__}},
              subject2 = {{12, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_8__}};
  s21_decimal actual, expected = {{60, 0, 0, __POSITIVE_AND_SCALE_EQUALS_16__}};

  performMultiplication(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

START_TEST(mul_standard_11) {
  s21_decimal subject1 = {{2, 0, 0, __POSITIVE_AND_SCALE_EQUALS_1__}},
              subject2 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual, expected = {{2, 0, 0, __POSITIVE_AND_SCALE_EQUALS_1__}};

  performMultiplication(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

START_TEST(mul_standard_12) {
  s21_decimal subject1 = {{0, 0, 0, __POSITIVE_AND_SCALE_EQUALS_8__}},
              subject2 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual, expected = {{0, 0, 0, __POSITIVE_AND_SCALE_EQUALS_8__}};

  performMultiplication(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

START_TEST(mul_standard_13) {
  s21_decimal subject1 = {{1, 0, 0, __POSITIVE_AND_SCALE_EQUALS_8__}},
              subject2 = {{1, 0, 0, __DECIMAL_NEGATIVE_INT_INFO__}};
  s21_decimal actual, expected = {{1, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_8__}};

  performMultiplication(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

START_TEST(mul_standard_14) {
  s21_decimal subject1 = {{0, 0, __DECIMAL_FULL_ROW__,
                           __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{1, 0, 0, __DECIMAL_NEGATIVE_INT_INFO__}};
  s21_decimal actual,
      expected = {{0, 0, __DECIMAL_FULL_ROW__, __DECIMAL_NEGATIVE_INT_INFO__}};

  performMultiplication(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

START_TEST(mul_border_1) {
  s21_decimal subject1 = {{__DECIMAL_FULL_ROW__, __DECIMAL_FULL_ROW__,
                           __DECIMAL_FULL_ROW__,
                           __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{2, 0, 0, __DECIMAL_NEGATIVE_INT_INFO__}};
  s21_decimal actual = {0}, expected = {0};
  performMultiplication(subject1, subject2, expected, &actual,
                        NUMBER_TOO_LARGE);
}
END_TEST

START_TEST(mul_border_2) {
  s21_decimal subject1 = {{__DECIMAL_FULL_ROW__, __DECIMAL_FULL_ROW__,
                           __DECIMAL_FULL_ROW__,
                           __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {
                  {__DECIMAL_FULL_ROW__, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual = {0}, expected = {0};
  performMultiplication(subject1, subject2, expected, &actual,
                        NUMBER_TOO_LARGE);
}
END_TEST

START_TEST(mul_border_3) {
  s21_decimal subject1 = {{0, __DECIMAL_FULL_ROW__, __DECIMAL_FULL_ROW__,
                           __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{1, 0, 0, __SCALE_IS_TOO_BIG__}};
  s21_decimal actual = {0}, expected = {0};
  performMultiplication(subject1, subject2, expected, &actual,
                        NUMBER_TOO_SMALL);
}
END_TEST

START_TEST(mul_border_4) {
  s21_decimal subject1 = {{0, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{__DECIMAL_FULL_ROW__, __DECIMAL_FULL_ROW__,
                           __DECIMAL_FULL_ROW__,
                           __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual, expected = {{0, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  performMultiplication(subject1, subject2, expected, &actual, ADD_OK);
}
END_TEST

Suite *arithmetic_suite(void) {
  Suite *suite = suite_create("arithmetics");
  TCase *add_func = tcase_create("Core");
  TCase *sub_func = tcase_create("Core");
  TCase *mul_func = tcase_create("Core");

  tcase_add_test(add_func, add_standard_1);
  tcase_add_test(add_func, add_standard_2);
  tcase_add_test(add_func, add_standard_3);
  tcase_add_test(add_func, add_standard_4);
  tcase_add_test(add_func, add_standard_5);
  tcase_add_test(add_func, add_standard_6);
  tcase_add_test(add_func, add_standard_7);
  tcase_add_test(add_func, add_standard_8);
  tcase_add_test(add_func, add_standard_9);
  tcase_add_test(add_func, add_standard_10);
  tcase_add_test(add_func, add_standard_11);
  tcase_add_test(add_func, add_standard_12);
  tcase_add_test(add_func, add_standard_13);
  tcase_add_test(add_func, add_standard_14);

  tcase_add_test(add_func, add_border_1);
  tcase_add_test(add_func, add_border_2);
  tcase_add_test(add_func, add_border_3);
  tcase_add_test(add_func, add_border_4);

  tcase_add_test(sub_func, sub_standard_1);
  tcase_add_test(sub_func, sub_standard_2);
  tcase_add_test(sub_func, sub_standard_3);
  tcase_add_test(sub_func, sub_standard_4);
  tcase_add_test(sub_func, sub_standard_5);
  tcase_add_test(sub_func, sub_standard_6);
  tcase_add_test(sub_func, sub_standard_7);
  tcase_add_test(sub_func, sub_standard_8);
  tcase_add_test(sub_func, sub_standard_9);
  tcase_add_test(sub_func, sub_standard_10);
  tcase_add_test(sub_func, sub_standard_11);
  tcase_add_test(sub_func, sub_standard_12);
  tcase_add_test(sub_func, sub_standard_13);
  tcase_add_test(sub_func, sub_standard_14);

  tcase_add_test(sub_func, sub_border_1);
  tcase_add_test(sub_func, sub_border_2);
  tcase_add_test(sub_func, sub_border_3);
  tcase_add_test(sub_func, sub_border_4);

  tcase_add_test(mul_func, mul_standard_1);
  tcase_add_test(mul_func, mul_standard_2);
  tcase_add_test(mul_func, mul_standard_3);
  tcase_add_test(mul_func, mul_standard_4);
  tcase_add_test(mul_func, mul_standard_5);
  tcase_add_test(mul_func, mul_standard_6);
  tcase_add_test(mul_func, mul_standard_7);
  tcase_add_test(mul_func, mul_standard_8);
  tcase_add_test(mul_func, mul_standard_9);
  tcase_add_test(mul_func, mul_standard_10);
  tcase_add_test(mul_func, mul_standard_11);
  tcase_add_test(mul_func, mul_standard_12);
  tcase_add_test(mul_func, mul_standard_13);
  tcase_add_test(mul_func, mul_standard_14);

  tcase_add_test(mul_func, mul_border_1);
  tcase_add_test(mul_func, mul_border_2);
  tcase_add_test(mul_func, mul_border_3);
  tcase_add_test(mul_func, mul_border_4);

  suite_add_tcase(suite, add_func);
  suite_add_tcase(suite, sub_func);
  suite_add_tcase(suite, mul_func);

  // TCase *debug_case = tcase_create("Core");
  // tcase_add_test(debug_case, mul_standard_10);
  // suite_add_tcase(suite, debug_case);

  return suite;
}
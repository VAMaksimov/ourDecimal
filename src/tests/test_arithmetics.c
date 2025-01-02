#include "test.h"

/* s21_from_int_to_decimal */

START_TEST(standard_1) {
  s21_decimal subject1 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual, expected = {{2, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  int result = s21_add(subject1, subject2, &actual);
  assertDecimal(expected, actual);
  ck_assert_int_eq(result, ADD_OK);
}
END_TEST

START_TEST(standard_2) {
  s21_decimal subject1 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{0, 1, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual, expected = {{1, 1, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  int result = s21_add(subject1, subject2, &actual);
  assertDecimal(expected, actual);
  ck_assert_int_eq(result, ADD_OK);
}
END_TEST

START_TEST(standard_3) {
  s21_decimal subject1 = {{25, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{75, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual, expected = {{100, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  int result = s21_add(subject1, subject2, &actual);
  assertDecimal(expected, actual);
  ck_assert_int_eq(result, ADD_OK);
}
END_TEST

START_TEST(standard_4) {
  s21_decimal subject1 = {{__DECIMAL_FULL_ROW__, 0, 0,
                           __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual, expected = {{0, 1, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  int result = s21_add(subject1, subject2, &actual);
  assertDecimal(expected, actual);
  ck_assert_int_eq(result, ADD_OK);
}
END_TEST

START_TEST(standard_5) {
  s21_decimal subject1 = {{__DECIMAL_FULL_ROW__, 0, 0,
                           __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {
                  {__DECIMAL_FULL_ROW__, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual, expected = {{__DECIMAL_FULL_ROW__ - 1, 1, 0,
                                   __DECIMAL_POSITIVE_INT_INFO__}};
  int result = s21_add(subject1, subject2, &actual);
  assertDecimal(expected, actual);
  ck_assert_int_eq(result, ADD_OK);
}
END_TEST

START_TEST(standard_6) {
  s21_decimal subject1 = {{25, 0, 0, __POSITIVE_AND_SCALE_EQUALS_1__}},
              subject2 = {{75, 0, 0, __POSITIVE_AND_SCALE_EQUALS_1__}};
  s21_decimal actual, expected = {{100, 0, 0, __POSITIVE_AND_SCALE_EQUALS_1__}};
  int result = s21_add(subject1, subject2, &actual);
  assertDecimal(expected, actual);
  ck_assert_int_eq(result, ADD_OK);
}
END_TEST

START_TEST(standard_7) {
  s21_decimal subject1 = {{__DECIMAL_FULL_ROW__, 0, 0,
                           __POSITIVE_AND_SCALE_EQUALS_8__}},
              subject2 = {{1, 0, 0, __POSITIVE_AND_SCALE_EQUALS_8__}};
  s21_decimal actual, expected = {{0, 1, 0, __POSITIVE_AND_SCALE_EQUALS_8__}};
  int result = s21_add(subject1, subject2, &actual);
  assertDecimal(expected, actual);
  ck_assert_int_eq(result, ADD_OK);
}
END_TEST

START_TEST(standard_8) {
  s21_decimal subject1 = {{__DECIMAL_FULL_ROW__, 0, 0,
                           __POSITIVE_AND_SCALE_EQUALS_1__}},
              subject2 = {{1, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_1__}};
  s21_decimal actual, expected = {{__DECIMAL_FULL_ROW__ - 1, 0, 0,
                                   __POSITIVE_AND_SCALE_EQUALS_1__}};
  int result = s21_add(subject1, subject2, &actual);
  assertDecimal(expected, actual);
  ck_assert_int_eq(result, ADD_OK);
}
END_TEST

// START_TEST(standard_1) {
//   s21_decimal subject1 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}},
//               subject2 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
//   s21_long_decimal actual,
//       expected = {{2, 0, 0, 0, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
//   actual = addition(subject1, subject2, &actual);
//   assertLongDecimal(expected, actual);
// }
// END_TEST

// START_TEST(standard_2) {
//   s21_decimal subject1 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}},
//               subject2 = {{0, 1, 0, __DECIMAL_POSITIVE_INT_INFO__}};
//   s21_long_decimal actual,
//       expected = {{1, 1, 0, 0, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
//   actual = addition(subject1, subject2, &actual);
//   assertLongDecimal(expected, actual);
// }
// END_TEST

Suite *arithmetic_suite(void) {
  Suite *suite = suite_create("arithmetics");
  TCase *add_func = tcase_create("Core");

  tcase_add_test(add_func, standard_1);
  tcase_add_test(add_func, standard_2);
  tcase_add_test(add_func, standard_3);
  tcase_add_test(add_func, standard_4);
  tcase_add_test(add_func, standard_5);
  tcase_add_test(add_func, standard_6);
  tcase_add_test(add_func, standard_7);
  tcase_add_test(add_func, standard_8);

  suite_add_tcase(suite, add_func);
  return suite;
}
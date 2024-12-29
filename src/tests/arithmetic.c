#include "test.h"

/* s21_from_int_to_decimal */

START_TEST(standard_1) {
  s21_decimal subject1 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_long_decimal actual,
      expected = {{2, 0, 0, 0, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  actual = addition(subject1, subject2, &actual);
  assertLongDecimal(expected, actual);
}
END_TEST

START_TEST(standard_2) {
  s21_decimal subject1 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{0, 1, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_long_decimal actual,
      expected = {{1, 1, 0, 0, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  actual = addition(subject1, subject2, &actual);
  assertLongDecimal(expected, actual);
}
END_TEST

END_TEST

Suite *arithmetic_suite(void) {
  Suite *suite = suite_create("s21_decimal");
  TCase *add_func = tcase_create("Core");

  tcase_add_test(add_func, standard_1);
  tcase_add_test(add_func, standard_2);

  suite_add_tcase(suite, add_func);
  return suite;
}
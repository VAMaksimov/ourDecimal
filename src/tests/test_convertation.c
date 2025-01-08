#include "test.h"

/* s21_from_int_to_decimal */

START_TEST(standard_1) {
  int subject = 1;
  s21_decimal actual, expected = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  int result = s21_from_int_to_decimal(subject, &actual);
  assertDecimal(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_SUCCESS);
}
END_TEST

START_TEST(standard_2) {
  int subject = 0;
  s21_decimal actual, expected = {{0, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  int result = s21_from_int_to_decimal(subject, &actual);
  assertDecimal(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_SUCCESS);
}
END_TEST

START_TEST(standard_3) {
  int subject = -1;
  s21_decimal actual, expected = {{1, 0, 0, __DECIMAL_NEGATIVE_INT_INFO__}};
  int result = s21_from_int_to_decimal(subject, &actual);
  assertDecimal(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_SUCCESS);
}
END_TEST

START_TEST(standard_4) {
  int subject = -9999999;
  s21_decimal actual,
      expected = {{0x98967f, 0, 0, __DECIMAL_NEGATIVE_INT_INFO__}};
  int result = s21_from_int_to_decimal(subject, &actual);
  assertDecimal(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_SUCCESS);
}
END_TEST

START_TEST(standard_5) {
  int subject = 7654321;
  s21_decimal actual,
      expected = {{0x74CBB1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  int result = s21_from_int_to_decimal(subject, &actual);
  assertDecimal(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_SUCCESS);
}
END_TEST

START_TEST(border_1) {
  int subject = __INT_MIN__;
  s21_decimal actual, expected = {{0, 0, 0, __DECIMAL_NEGATIVE_INT_INFO__}};
  int result = s21_from_int_to_decimal(subject, &actual);
  assertDecimal(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_SUCCESS);
}
END_TEST

START_TEST(border_2) {
  int subject = __INT_MAX__;
  s21_decimal actual, expected = {{__DECIMAL_LOWER_MIDPOINT__, 0, 0,
                                   __DECIMAL_POSITIVE_INT_INFO__}};
  int result = s21_from_int_to_decimal(subject, &actual);
  assertDecimal(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_SUCCESS);
}
END_TEST

/* s21_from_decimal_to_int */

START_TEST(standard_6) {
  s21_decimal subject = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  int actual, expected = 1;
  int result = s21_from_decimal_to_int(subject, &actual);
  ck_assert_int_eq(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_SUCCESS);
}
END_TEST

START_TEST(standard_7) {
  s21_decimal subject = {{0, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  int actual, expected = 0;
  int result = s21_from_decimal_to_int(subject, &actual);
  ck_assert_int_eq(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_SUCCESS);
}
END_TEST

START_TEST(standard_8) {
  s21_decimal subject = {{1, 0, 0, __DECIMAL_NEGATIVE_INT_INFO__}};
  int actual, expected = -1;
  int result = s21_from_decimal_to_int(subject, &actual);
  ck_assert_int_eq(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_SUCCESS);
}
END_TEST

START_TEST(standard_9) {
  s21_decimal subject = {{0x98967f, 0, 0, __DECIMAL_NEGATIVE_INT_INFO__}};
  int actual, expected = -9999999;
  int result = s21_from_decimal_to_int(subject, &actual);
  ck_assert_int_eq(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_SUCCESS);
}
END_TEST

START_TEST(standard_10) {
  s21_decimal subject = {{0x74CBB1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  int actual, expected = 7654321;
  int result = s21_from_decimal_to_int(subject, &actual);
  ck_assert_int_eq(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_SUCCESS);
}
END_TEST

START_TEST(border_3) {
  s21_decimal subject = {{0, 0, 0, __DECIMAL_NEGATIVE_INT_INFO__}};
  int actual, expected = __INT_MIN__;
  int result = s21_from_decimal_to_int(subject, &actual);
  ck_assert_int_eq(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_SUCCESS);
}
END_TEST

START_TEST(border_4) {
  s21_decimal subject = {
      {__DECIMAL_LOWER_MIDPOINT__, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  int actual, expected = __INT_MAX__;
  int result = s21_from_decimal_to_int(subject, &actual);
  ck_assert_int_eq(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_SUCCESS);
}
END_TEST

START_TEST(irregular_1) {
  s21_decimal subject = {{1, 1, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  int actual = 0, expected = 0;
  int result = s21_from_decimal_to_int(subject, &actual);
  ck_assert_int_eq(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_ERROR);
}
END_TEST

START_TEST(irregular_2) {
  s21_decimal subject = {
      {__DECIMAL_UPPER_MIDPOINT__, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  int actual = 0, expected = 0;
  int result = s21_from_decimal_to_int(subject, &actual);
  ck_assert_int_eq(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_ERROR);
}
END_TEST

START_TEST(irregular_3) {
  s21_decimal subject = {
      {__DECIMAL_UPPER_MIDPOINT__, 0, 0, __DECIMAL_NEGATIVE_INT_INFO__}};
  int actual = 0, expected = 0;
  int result = s21_from_decimal_to_int(subject, &actual);
  ck_assert_int_eq(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_ERROR);
}
END_TEST

START_TEST(irregular_4) {
  s21_decimal subject = {{__DECIMAL_FULL_ROW__, __DECIMAL_FULL_ROW__,
                          __DECIMAL_FULL_ROW__, __DECIMAL_POSITIVE_INT_INFO__}};
  int actual = 0, expected = 0;
  int result = s21_from_decimal_to_int(subject, &actual);
  ck_assert_int_eq(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_ERROR);
}
END_TEST

Suite *convert_suite(void) {
  Suite *suite = suite_create("convertation");
  TCase *int_to_dec = tcase_create("Core");
  TCase *dec_to_int = tcase_create("Core");

  tcase_add_test(int_to_dec, standard_1);
  tcase_add_test(int_to_dec, standard_2);
  tcase_add_test(int_to_dec, standard_3);
  tcase_add_test(int_to_dec, standard_4);
  tcase_add_test(int_to_dec, standard_5);
  tcase_add_test(int_to_dec, border_1);
  tcase_add_test(int_to_dec, border_2);

  tcase_add_test(dec_to_int, standard_6);
  tcase_add_test(dec_to_int, standard_7);
  tcase_add_test(dec_to_int, standard_8);
  tcase_add_test(dec_to_int, standard_9);
  tcase_add_test(dec_to_int, standard_10);
  tcase_add_test(dec_to_int, border_3);
  tcase_add_test(dec_to_int, border_4);
  tcase_add_test(dec_to_int, irregular_1);
  tcase_add_test(dec_to_int, irregular_2);
  tcase_add_test(dec_to_int, irregular_3);
  tcase_add_test(dec_to_int, irregular_4);

  suite_add_tcase(suite, int_to_dec);
  suite_add_tcase(suite, dec_to_int);
  return suite;
}
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

START_TEST(standard_11) {
  s21_decimal subject = {{0x74CBB1, 0, 0, __POSITIVE_AND_SCALE_EQUALS_1__}};
  int actual, expected = 765432;
  int result = s21_from_decimal_to_int(subject, &actual);
  ck_assert_int_eq(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_SUCCESS);
}
END_TEST

START_TEST(standard_12) {
  s21_decimal subject = {{0x74CBB1, 0, 0, __POSITIVE_AND_SCALE_EQUALS_2__}};
  int actual, expected = 76543;
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
// float to decimal
START_TEST(standard_normal) {
  float subject = 987.654;
  s21_decimal actual, expected = {{987654, 0, 0, 0x30000}};
  int result = s21_from_float_to_decimal(subject, &actual);
  assertDecimal(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_SUCCESS);
}
END_TEST

START_TEST(standard_negative) {
  float subject = -987.654;
  s21_decimal actual, expected = {{987654, 0, 0, 0x80030000}};
  int result = s21_from_float_to_decimal(subject, &actual);
  assertDecimal(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_SUCCESS);
}
END_TEST

START_TEST(too_small_value) {
  float subject = 1e-30;
  s21_decimal actual;
  int result = s21_from_float_to_decimal(subject, &actual);
  ck_assert_int_eq(result, CONVERTATION_ERROR);
}
END_TEST

START_TEST(too_large_value) {
  float subject = 1e40;
  s21_decimal actual;
  int result = s21_from_float_to_decimal(subject, &actual);
  ck_assert_int_eq(result, CONVERTATION_ERROR);
}
END_TEST

START_TEST(single_digit) {
  float subject = 5.0;
  s21_decimal actual, expected = {{5, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  int result = s21_from_float_to_decimal(subject, &actual);
  assertDecimal(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_SUCCESS);
}
END_TEST

START_TEST(seven_digits) {
  float subject = 1234567.0;
  s21_decimal actual,
      expected = {{1234567, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  int result = s21_from_float_to_decimal(subject, &actual);
  assertDecimal(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_SUCCESS);
}

START_TEST(more_than_seven_digits) {
  float subject = 12345678.9;
  s21_decimal actual,
      expected = {{12345679, 0, 0,
                   __DECIMAL_POSITIVE_INT_INFO__}};  // ожидаем округление
  int result = s21_from_float_to_decimal(subject, &actual);
  assertDecimal(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_SUCCESS);
}
END_TEST
/* s21_from_decimal_to_float */

/* Стандартный случай - положительное число */
START_TEST(standard_positive) {
  s21_decimal subject = {{987654, 0, 0, 0}};
  float actual, expected = 987654;
  int result = s21_from_decimal_to_float(subject, &actual);
  ck_assert_float_eq(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_SUCCESS);
}
END_TEST

/* Стандартный случай - отрицательное число */
START_TEST(standard_negative2) {
  s21_decimal subject = {{987654, 0, 0, __DECIMAL_NEGATIVE_INT_INFO__}};
  float actual, expected = -987654.0;
  int result = s21_from_decimal_to_float(subject, &actual);
  ck_assert_float_eq(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_SUCCESS);
}
END_TEST

/* Стандартный случай - число с плавающей точкой */
START_TEST(standard_float) {
  s21_decimal subject = {{987654, 0, 0, 0}};
  float actual, expected = 987654.0;
  int result = s21_from_decimal_to_float(subject, &actual);
  ck_assert_float_eq(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_SUCCESS);
}
END_TEST

/* Нулевое число */
START_TEST(zero) {
  s21_decimal subject = {{0, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  float actual, expected = 0.0;
  int result = s21_from_decimal_to_float(subject, &actual);
  ck_assert_float_eq(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_SUCCESS);
}
END_TEST

/* Маленькое число (близкое к нулю) */
START_TEST(very_small) {
  s21_decimal subject = {{1, 0, 0, 0x50000}};
  float actual, expected = 0.00001;
  int result = s21_from_decimal_to_float(subject, &actual);
  ck_assert_float_eq(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_SUCCESS);
}
END_TEST

/* Слишком маленькое значение (ошибка конвертации) */
START_TEST(too_small) {
  s21_decimal subject = {{1, 0, 0, 0x80001}};
  float actual;
  int result = s21_from_decimal_to_float(subject, &actual);
  ck_assert_int_eq(result, CONVERTATION_ERROR);
}
END_TEST

/* Очень большое число (ошибка конвертации) */
START_TEST(too_large) {
  s21_decimal subject = {{__DECIMAL_FULL_ROW__, __DECIMAL_FULL_ROW__, 0,
                          __DECIMAL_POSITIVE_INT_INFO__}};
  float actual;
  int result = s21_from_decimal_to_float(subject, &actual);
  ck_assert_int_eq(result, CONVERTATION_ERROR);
}
END_TEST

/* Проверка на бесконечность (ошибка конвертации) */
START_TEST(infinity) {
  s21_decimal subject = {{4294967295, 4294967295, 4294967295, 4294967295}};
  float actual;
  int result = s21_from_decimal_to_float(subject, &actual);
  ck_assert_int_eq(result, CONVERTATION_ERROR);
}
END_TEST

/* Проверка некорректного десятичного числа */
START_TEST(incorrect_decimal) {
  s21_decimal subject = {{1, 1, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  float actual;
  int result = s21_from_decimal_to_float(subject, &actual);
  ck_assert_int_eq(result, CONVERTATION_ERROR);
}
END_TEST

Suite *convert_suite(void) {
  Suite *suite = suite_create("convertation");
  TCase *int_to_dec = tcase_create("int_to_decimal");
  TCase *dec_to_int = tcase_create("decimal_to_int");
  TCase *float_to_decimal = tcase_create("float_to_decimal");
  TCase *decimal_to_float = tcase_create("decimal_to_float");

  // int_to_decimal tests
  tcase_add_test(int_to_dec, standard_1);
  tcase_add_test(int_to_dec, standard_2);
  tcase_add_test(int_to_dec, standard_3);
  tcase_add_test(int_to_dec, standard_4);
  tcase_add_test(int_to_dec, standard_5);
  tcase_add_test(int_to_dec, border_1);
  tcase_add_test(int_to_dec, border_2);

  // decimal_to_int tests
  tcase_add_test(dec_to_int, standard_6);
  tcase_add_test(dec_to_int, standard_7);
  tcase_add_test(dec_to_int, standard_8);
  tcase_add_test(dec_to_int, standard_9);
  tcase_add_test(dec_to_int, standard_10);
  tcase_add_test(dec_to_int, standard_11);
  tcase_add_test(dec_to_int, standard_12);
  tcase_add_test(dec_to_int, border_4);
  tcase_add_test(dec_to_int, irregular_1);
  tcase_add_test(dec_to_int, irregular_2);
  tcase_add_test(dec_to_int, irregular_3);
  tcase_add_test(dec_to_int, irregular_4);

  // float_to_decimal tests
  tcase_add_test(float_to_decimal, standard_normal);
  tcase_add_test(float_to_decimal, standard_negative);
  tcase_add_test(float_to_decimal, too_small_value);
  tcase_add_test(float_to_decimal, too_large_value);
  tcase_add_test(float_to_decimal, single_digit);
  tcase_add_test(float_to_decimal, seven_digits);
  tcase_add_test(float_to_decimal, more_than_seven_digits);

  // decimal to float tests
  tcase_add_test(decimal_to_float, standard_positive);
  tcase_add_test(decimal_to_float, standard_negative2);
  tcase_add_test(decimal_to_float, standard_float);
  tcase_add_test(decimal_to_float, zero);
  tcase_add_test(decimal_to_float, very_small);
  tcase_add_test(decimal_to_float, too_small);
  tcase_add_test(decimal_to_float, too_large);
  tcase_add_test(decimal_to_float, infinity);
  tcase_add_test(decimal_to_float, incorrect_decimal);

  suite_add_tcase(suite, int_to_dec);
  suite_add_tcase(suite, dec_to_int);
  suite_add_tcase(suite, float_to_decimal);
  suite_add_tcase(suite, decimal_to_float);

  return suite;
}

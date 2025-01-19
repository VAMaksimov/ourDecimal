#include <check.h>
#include <stdio.h>

#include "../s21_decimal.h"
#include "test.h"

START_TEST(test_s21_truncate_zero) {
    s21_decimal value = {{0, 0, 0, 0}};
    s21_decimal expected = {{0, 0, 0, 0}};
    s21_decimal result = {0};

    int ret = s21_truncate(value, &result);
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_truncate_large_scale) {
    s21_decimal value = {{12345, 0, 0, 0}};
    setScale(&value, 10);  // Масштаб 10 (12345 * 10^-10)
    s21_decimal expected = {{0, 0, 0, 0}};  // Ожидаемый результат 0
    s21_decimal result = {0};

    int ret = s21_truncate(value, &result);
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_truncate_negative) {
    s21_decimal value = {{12345, 0, 0, 0}};
    setScale(&value, 3);  // Масштаб 3 (12345 * 10^-3)
    setBit(&value, MINUS_BIT_INDEX);  // Минус
    s21_decimal expected = {{12, 0, 0, 0}};  // Ожидаемый результат -12
    setBit(&expected, MINUS_BIT_INDEX);
    s21_decimal result = {0};

    int ret = s21_truncate(value, &result);
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_truncate_negative_large) {
    s21_decimal value = {{123456789, 0, 0, 0}};
    setScale(&value, 10);  // Масштаб 10 (123456789 * 10^-10)
    setBit(&value, MINUS_BIT_INDEX);  // Минус
    s21_decimal expected = {{0, 0, 0, 0}};  // Ожидаемый результат -123456
    setBit(&expected, MINUS_BIT_INDEX);
    s21_decimal result = {0};

    int ret = s21_truncate(value, &result);
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_truncate_large_value) {
    s21_decimal value = {{123456789, 0, 0, 0}};
    setScale(&value, 4);  // Масштаб 4 (123456789 * 10^-4)
    s21_decimal expected = {{12345, 0, 0, 0}};  // Ожидаемый результат 1234567
    s21_decimal result = {0};

    int ret = s21_truncate(value, &result);
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_truncate_small_fraction) {
    s21_decimal value = {{123456789, 0, 0, 0}};
    setScale(&value, 9);  // Масштаб 9 (123456789 * 10^-9)
    s21_decimal expected = {{0, 0, 0, 0}};  // Ожидаемый результат 123
    s21_decimal result = {0};

    int ret = s21_truncate(value, &result);
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_truncate_large_value_negative) {
    s21_decimal value = {{123456789, 0, 0, 0}};
    setScale(&value, 6);  // Масштаб 6 (123456789 * 10^-6)
    setBit(&value, MINUS_BIT_INDEX);  // Минус
    s21_decimal expected = {{123, 0, 0, 0}};  // Ожидаемый результат -123457
    setBit(&expected, MINUS_BIT_INDEX);
    s21_decimal result = {0};

    int ret = s21_truncate(value, &result);
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_negate_positive_to_negative) {
  s21_decimal value = {{12345, 0, 0, 0}};
  s21_decimal expected = {{12345, 0, 0, 0}};
  setBit(&expected, MINUS_BIT_INDEX);  // Устанавливаем минус
  s21_decimal result = {0};

  int ret = s21_negate(value, &result);
  ck_assert_int_eq(ret, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_negate_negative_to_positive) {
  s21_decimal value = {{12345, 0, 0, 0}};
  setBit(&value, MINUS_BIT_INDEX);  // Устанавливаем минус
  s21_decimal expected = {{12345, 0, 0, 0}};  // Ожидаемое значение без минуса
  s21_decimal result = {0};

  int ret = s21_negate(value, &result);
  ck_assert_int_eq(ret, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_negate_zero) {
  s21_decimal value = {{0, 0, 0, 0}};
  ;
  s21_decimal result = {0};

  int ret = s21_negate(value, &result);
  ck_assert_int_eq(ret, 0);  // Проверяем, что функция завершилась успешно
  // Проверяем, что результат — это отрицательный ноль
  ck_assert_int_eq(isSetBit(result, MINUS_BIT_INDEX),
                   1);  // Проверяем бит знака
  ck_assert_int_eq(result.bits[0], 0);  // Проверяем, что мантисса равна 0
}
END_TEST

START_TEST(test_s21_negate_large_number) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal expected = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  setBit(&expected, MINUS_BIT_INDEX);
  s21_decimal result = {0};

  int ret = s21_negate(value, &result);
  ck_assert_int_eq(ret, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_floor_positive) {
    s21_decimal value = {{12345, 0, 0, 0}};
    setScale(&value, 3);
    s21_decimal expected = {{12, 0, 0, 0}};
    s21_decimal result = {0};

    int ret = s21_floor(value, &result);
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_floor_negative) {
    s21_decimal value = {{12345, 0, 0, 0}};
    setScale(&value, 3);
    setBit(&value, MINUS_BIT_INDEX);
    s21_decimal expected = {{13, 0, 0, 0}};
    setBit(&expected, MINUS_BIT_INDEX);
    s21_decimal result = {0};

    int ret = s21_floor(value, &result);
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_round_positive) {
    s21_decimal value = {{12345, 0, 0, 0}};
    setScale(&value, 3);
    s21_decimal expected = {{12, 0, 0, 0}};
    s21_decimal result = {0};

    int ret = s21_round(value, &result);
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_round_negative) {
    s21_decimal value = {{12555, 0, 0, 0}};
    setScale(&value, 3);
    setBit(&value, MINUS_BIT_INDEX);
    s21_decimal expected = {{13, 0, 0, 0}};
    setBit(&expected, MINUS_BIT_INDEX);
    s21_decimal result = {0};

    int ret = s21_round(value, &result);
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_round_exact_half) {
    s21_decimal value = {{5000, 0, 0, 0}};
    setScale(&value, 3); // 5.000
    s21_decimal expected = {{5, 0, 0, 0}};
    s21_decimal result = {0};

    int ret = s21_round(value, &result);
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

// Дополнительные тесты для floor
START_TEST(test_s21_floor_zero) {
    s21_decimal value = {{0, 0, 0, 0}};
    s21_decimal expected = {{0, 0, 0, 0}};
    s21_decimal result = {0};

    int ret = s21_floor(value, &result);
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_floor_large_negative) {
    s21_decimal value = {{12345678, 0, 0, 0}};
    setScale(&value, 4);  // -1234.5678
    setBit(&value, MINUS_BIT_INDEX);
    s21_decimal expected = {{1235, 0, 0, 0}};  // -1235
    setBit(&expected, MINUS_BIT_INDEX);
    s21_decimal result = {0};

    int ret = s21_floor(value, &result);
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

// Дополнительные тесты для round
START_TEST(test_s21_round_zero) {
    s21_decimal value = {{0, 0, 0, 0}};
    s21_decimal expected = {{0, 0, 0, 0}};
    s21_decimal result = {0};

    int ret = s21_round(value, &result);
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_round_large_positive) {
    s21_decimal value = {{12345678, 0, 0, 0}};
    setScale(&value, 5);  // 123.45678
    s21_decimal expected = {{123, 0, 0, 0}};  // Округление до 123
    s21_decimal result = {0};

    int ret = s21_round(value, &result);
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_round_lev) {
    s21_decimal value = {{0xFFFFFFFF, 0, 0, 0}};
    setScale(&value, 1); 
    s21_decimal expected = {{429496730, 0, 0, 0}}; 
    s21_decimal result = {0};

    int ret = s21_round(value, &result);
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_round_large_half) {
    s21_decimal value = {{50000, 0, 0, 0}};
    setScale(&value, 4);  // 5.0000
    s21_decimal expected = {{5, 0, 0, 0}};
    s21_decimal result = {0};

    int ret = s21_round(value, &result);
    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

// Добавление новых тестов в соответствующие TCase
Suite *other_suite(void) {
  Suite *s = suite_create("s21_others");

TCase *tc_truncate = tcase_create("truncate");
  tcase_add_test(tc_truncate, test_s21_truncate_negative);
  tcase_add_test(tc_truncate, test_s21_truncate_zero);
  tcase_add_test(tc_truncate, test_s21_truncate_large_scale);
  tcase_add_test(tc_truncate, test_s21_truncate_small_fraction);
  tcase_add_test(tc_truncate, test_s21_truncate_large_value);
  tcase_add_test(tc_truncate, test_s21_truncate_large_value_negative);
  tcase_add_test(tc_truncate, test_s21_truncate_negative_large);
  suite_add_tcase(s, tc_truncate);


  TCase *tc_negate = tcase_create("negate");
  tcase_add_test(tc_negate, test_s21_negate_positive_to_negative);
  tcase_add_test(tc_negate, test_s21_negate_negative_to_positive);
  tcase_add_test(tc_negate, test_s21_negate_zero);
  tcase_add_test(tc_negate, test_s21_negate_large_number);
  suite_add_tcase(s, tc_negate);

  TCase *tc_floor = tcase_create("floor");
  tcase_add_test(tc_floor, test_s21_floor_positive);
  tcase_add_test(tc_floor, test_s21_floor_negative);
  tcase_add_test(tc_floor, test_s21_floor_zero);
  tcase_add_test(tc_floor, test_s21_floor_large_negative);
  suite_add_tcase(s, tc_floor);

  TCase *tc_round = tcase_create("round");
  tcase_add_test(tc_round, test_s21_round_positive);
  tcase_add_test(tc_round, test_s21_round_negative);
  tcase_add_test(tc_round, test_s21_round_exact_half);
  tcase_add_test(tc_round, test_s21_round_zero);
  tcase_add_test(tc_round, test_s21_round_large_positive);
  tcase_add_test(tc_round, test_s21_round_large_half);
  tcase_add_test(tc_round, test_s21_round_lev);
  suite_add_tcase(s, tc_round);

  return s;
}

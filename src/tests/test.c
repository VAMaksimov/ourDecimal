#include "test.h"

void assertDecimal(s21_decimal expected, s21_decimal actual) {
  int row = ROW_NUMBER;
  while (row--) ck_assert_int_eq(expected.bits[row], actual.bits[row]);
}

START_TEST(standard_1) {
  int subject = 1;
  s21_decimal actual, expected = {{0, 0, 1, __DECIMAL_POSITIVE_INT_INFO__}};
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
  s21_decimal actual, expected = {{0, 0, 1, __DECIMAL_NEGATIVE_INT_INFO__}};
  int result = s21_from_int_to_decimal(subject, &actual);
  assertDecimal(expected, actual);
  ck_assert_int_eq(result, CONVERTATION_SUCCESS);
}
END_TEST

Suite *s21_decimal_suite(void) {
  Suite *suite = suite_create("s21_decimal");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, standard_1);
  tcase_add_test(tc_core, standard_2);
  tcase_add_test(tc_core, standard_3);

  suite_add_tcase(suite, tc_core);
  return suite;
}

int main(void) {
  int number_failed;
  Suite *suite = s21_decimal_suite();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return number_failed == 0 ? 0 : 1;
}
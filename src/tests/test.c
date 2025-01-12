#include "test.h"

void assertDecimal(s21_decimal expected, s21_decimal actual) {
  int row = ROW_NUMBER;
  while (row--) {
    if (expected.bits[row] != actual.bits[row])
      printf("Error on row %d\n", row + 1);
    ck_assert_int_eq(expected.bits[row], actual.bits[row]);
  }
}

void assertLongDecimal(s21_long_decimal expected, s21_long_decimal actual) {
  int row = LONG_ROW_NUMBER;
  while (row--) ck_assert_int_eq(expected.bits[row], actual.bits[row]);
}

int main(void) {
  int fails_count = 0;
  Suite *suite_list[] = {convert_suite(),    arithmetic_suite(),
                         comparison_suite(), other_suite(),
                         div_suite(),        NULL};

  for (Suite **current_suite = suite_list; *current_suite != NULL;
       current_suite++) {
    SRunner *runner = srunner_create(*current_suite);
    srunner_run_all(runner, CK_NORMAL);
    int suite_failed = srunner_ntests_failed(runner);
    fails_count += suite_failed;
    if (suite_failed)
      printf("\033[31mFAILED\033[0m\n");
    else
      printf("\033[32mPASSED\033[0m\n");
    srunner_free(runner);
  }
  if (fails_count)
    printf("\n\033[31m========= FAILED: %d =========\n", fails_count);
  return 0;
}
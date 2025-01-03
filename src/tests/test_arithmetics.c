#include "test.h"

/* s21_from_int_to_decimal */

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

START_TEST(standard_1) {
  s21_decimal subject1 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual, expected = {{2, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}},
                      expectedSub = {{0, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  performAddition(subject1, subject2, expected, &actual, ADD_OK);
  performSubtraction(subject1, subject2, expectedSub, &actual, ADD_OK);
}
END_TEST

START_TEST(standard_2) {
  s21_decimal subject1 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{0, 1, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual, expected = {{1, 1, 0, __DECIMAL_POSITIVE_INT_INFO__}},
                      expectedSub = {{__DECIMAL_FULL_ROW__, 0, 0,
                                      __DECIMAL_NEGATIVE_INT_INFO__}};

  performAddition(subject1, subject2, expected, &actual, ADD_OK);
  performSubtraction(subject1, subject2, expectedSub, &actual, ADD_OK);
}
END_TEST

START_TEST(standard_3) {
  s21_decimal subject1 = {{25, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{75, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual, expected = {{100, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}},
                      expectedSub = {{50, 0, 0, __DECIMAL_NEGATIVE_INT_INFO__}};

  performAddition(subject1, subject2, expected, &actual, ADD_OK);
  performSubtraction(subject1, subject2, expectedSub, &actual, ADD_OK);
}
END_TEST

START_TEST(standard_4) {
  s21_decimal subject1 = {{__DECIMAL_FULL_ROW__, 0, 0,
                           __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual, expected = {{0, 1, 0, __DECIMAL_POSITIVE_INT_INFO__}},
                      expectedSub = {{__DECIMAL_FULL_ROW__ - 1, 0, 0,
                                      __DECIMAL_POSITIVE_INT_INFO__}};

  performAddition(subject1, subject2, expected, &actual, ADD_OK);
  performSubtraction(subject1, subject2, expectedSub, &actual, ADD_OK);
}
END_TEST

START_TEST(standard_5) {
  s21_decimal subject1 = {{__DECIMAL_FULL_ROW__, 0, 0,
                           __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {
                  {__DECIMAL_FULL_ROW__, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual,
      expected = {{__DECIMAL_FULL_ROW__ - 1, 1, 0,
                   __DECIMAL_POSITIVE_INT_INFO__}},
      expectedSub = {{0, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};

  performAddition(subject1, subject2, expected, &actual, ADD_OK);
  performSubtraction(subject1, subject2, expectedSub, &actual, ADD_OK);
}
END_TEST

START_TEST(standard_6) {
  s21_decimal subject1 = {{25, 0, 0, __POSITIVE_AND_SCALE_EQUALS_1__}},
              subject2 = {{75, 0, 0, __POSITIVE_AND_SCALE_EQUALS_1__}};
  s21_decimal actual,
      expected = {{100, 0, 0, __POSITIVE_AND_SCALE_EQUALS_1__}},
      expectedSub = {{50, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_1__}};

  performAddition(subject1, subject2, expected, &actual, ADD_OK);
  performSubtraction(subject1, subject2, expectedSub, &actual, ADD_OK);
}
END_TEST

START_TEST(standard_7) {
  s21_decimal subject1 = {{__DECIMAL_FULL_ROW__, 0, 0,
                           __POSITIVE_AND_SCALE_EQUALS_8__}},
              subject2 = {{1, 0, 0, __POSITIVE_AND_SCALE_EQUALS_8__}};
  s21_decimal actual, expected = {{0, 1, 0, __POSITIVE_AND_SCALE_EQUALS_8__}},
                      expectedSub = {{__DECIMAL_FULL_ROW__ - 1, 0, 0,
                                      __POSITIVE_AND_SCALE_EQUALS_8__}};

  performAddition(subject1, subject2, expected, &actual, ADD_OK);
  performSubtraction(subject1, subject2, expectedSub, &actual, ADD_OK);
}
END_TEST

START_TEST(standard_8) {
  s21_decimal subject1 = {{__DECIMAL_FULL_ROW__, 0, 0,
                           __POSITIVE_AND_SCALE_EQUALS_1__}},
              subject2 = {{1, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_1__}};
  s21_decimal actual,
      expected = {{__DECIMAL_FULL_ROW__ - 1, 0, 0,
                   __POSITIVE_AND_SCALE_EQUALS_1__}},
      expectedSub = {{0, 1, 0, __POSITIVE_AND_SCALE_EQUALS_1__}};

  performAddition(subject1, subject2, expected, &actual, ADD_OK);
  performSubtraction(subject1, subject2, expectedSub, &actual, ADD_OK);
}
END_TEST

START_TEST(standard_9) {
  s21_decimal subject1 = {{25, 0, 0, __POSITIVE_AND_SCALE_EQUALS_1__}},
              subject2 = {{75, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_1__}};
  s21_decimal actual,
      expected = {{50, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_1__}},
      expectedSub = {{100, 0, 0, __POSITIVE_AND_SCALE_EQUALS_1__}};

  performAddition(subject1, subject2, expected, &actual, ADD_OK);
  performSubtraction(subject1, subject2, expectedSub, &actual, ADD_OK);
}
END_TEST

START_TEST(standard_10) {
  s21_decimal subject1 = {{25, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_8__}},
              subject2 = {{75, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_8__}};
  s21_decimal actual,
      expected = {{100, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_8__}},
      expectedSub = {{50, 0, 0, __POSITIVE_AND_SCALE_EQUALS_8__}};

  performAddition(subject1, subject2, expected, &actual, ADD_OK);
  performSubtraction(subject1, subject2, expectedSub, &actual, ADD_OK);
}
END_TEST

START_TEST(standard_11) {
  s21_decimal subject1 = {{2, 0, 0, __POSITIVE_AND_SCALE_EQUALS_1__}},
              subject2 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual,
      expected = {{12, 0, 0, __POSITIVE_AND_SCALE_EQUALS_1__}},
      expectedSub = {{8, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_1__}};

  performAddition(subject1, subject2, expected, &actual, ADD_OK);
  performSubtraction(subject1, subject2, expectedSub, &actual, ADD_OK);
}
END_TEST

START_TEST(standard_12) {
  s21_decimal subject1 = {{0, 0, 0, __POSITIVE_AND_SCALE_EQUALS_8__}},
              subject2 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual,
      expected = {{100000000, 0, 0, __POSITIVE_AND_SCALE_EQUALS_8__}},
      expectedSub = {{100000000, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_8__}};

  performAddition(subject1, subject2, expected, &actual, ADD_OK);
  performSubtraction(subject1, subject2, expectedSub, &actual, ADD_OK);
}
END_TEST

START_TEST(standard_13) {
  s21_decimal subject1 = {{1, 0, 0, __POSITIVE_AND_SCALE_EQUALS_8__}},
              subject2 = {{1, 0, 0, __DECIMAL_NEGATIVE_INT_INFO__}};
  s21_decimal actual,
      expected = {{99999999, 0, 0, __NEGATIVE_AND_SCALE_EQUALS_8__}},
      expectedSub = {{100000001, 0, 0, __POSITIVE_AND_SCALE_EQUALS_8__}};

  performAddition(subject1, subject2, expected, &actual, ADD_OK);
  performSubtraction(subject1, subject2, expectedSub, &actual, ADD_OK);
}
END_TEST

START_TEST(standard_14) {
  s21_decimal subject1 = {{0, 0, __DECIMAL_FULL_ROW__,
                           __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{1, 0, 0, __DECIMAL_NEGATIVE_INT_INFO__}};
  s21_decimal actual,
      expected = {{__DECIMAL_FULL_ROW__, __DECIMAL_FULL_ROW__,
                   __DECIMAL_FULL_ROW__ - 1, __DECIMAL_POSITIVE_INT_INFO__}},
      expectedSub = {
          {1, 0, __DECIMAL_FULL_ROW__, __DECIMAL_POSITIVE_INT_INFO__}};

  performAddition(subject1, subject2, expected, &actual, ADD_OK);
  performSubtraction(subject1, subject2, expectedSub, &actual, ADD_OK);
}
END_TEST

START_TEST(border_1) {
  s21_decimal subject1 = {{__DECIMAL_FULL_ROW__, __DECIMAL_FULL_ROW__,
                           __DECIMAL_FULL_ROW__,
                           __DECIMAL_POSITIVE_INT_INFO__}},
              subject2 = {{1, 0, 0, __DECIMAL_POSITIVE_INT_INFO__}};
  s21_decimal actual = {0}, expected = {0};
  performAddition(subject1, subject2, expected, &actual, NUMBER_TOO_LARGE);
}
END_TEST

START_TEST(border_2) {
  s21_decimal subject1 = {{__DECIMAL_FULL_ROW__, __DECIMAL_FULL_ROW__,
                           __DECIMAL_FULL_ROW__,
                           __DECIMAL_NEGATIVE_INT_INFO__}},
              subject2 = {
                  {__DECIMAL_FULL_ROW__, 0, 0, __DECIMAL_NEGATIVE_INT_INFO__}};
  s21_decimal actual = {0}, expected = {0};
  performAddition(subject1, subject2, expected, &actual, NUMBER_TOO_SMALL);
}
END_TEST

START_TEST(border_3) {
  s21_decimal subject1 = {{0, __DECIMAL_FULL_ROW__, __DECIMAL_FULL_ROW__,
                           __DECIMAL_NEGATIVE_INT_INFO__}},
              subject2 = {{__DECIMAL_FULL_ROW__, 0, 0, __SCALE_IS_TOO_BIG__}};
  s21_decimal actual = {0}, expected = {0};
  performAddition(subject1, subject2, expected, &actual, NUMBER_TOO_SMALL);
}
END_TEST

START_TEST(border_4) {
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
  tcase_add_test(add_func, standard_9);
  tcase_add_test(add_func, standard_10);
  tcase_add_test(add_func, standard_11);
  tcase_add_test(add_func, standard_12);
  tcase_add_test(add_func, standard_13);
  tcase_add_test(add_func, standard_14);

  tcase_add_test(add_func, border_1);
  tcase_add_test(add_func, border_2);
  tcase_add_test(add_func, border_3);
  tcase_add_test(add_func, border_4);

  suite_add_tcase(suite, add_func);
  return suite;
}
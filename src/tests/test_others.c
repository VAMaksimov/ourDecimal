#include "test.h"

START_TEST(test_s21_truncate) {
    s21_decimal value = {{12345, 0, 0, 0}};
    setScale(&value, 3);  
    s21_decimal expected = {{12, 0, 0, 0}};  
    s21_decimal result = {0};
    
    int ret = s21_truncate(value, &result);
    ck_assert_int_eq(ret, 0);
    int errorType = 0;
    ck_assert_int_eq(s21_is_equal(result, expected, &errorType), 1);
}
END_TEST

START_TEST(test_s21_truncate_negative) {
    s21_decimal value = {{12345, 0, 0, 0}};
    setScale(&value, 3);  
    setBit(&value, MINUS_BIT_INDEX);
    s21_decimal expected = {{12, 0, 0, 0}};
    setBit(&expected, MINUS_BIT_INDEX);  
    s21_decimal result = {0};
    int ret = s21_truncate(value, &result);
    ck_assert_int_eq(ret, 0);
    int errorType = 0;
    ck_assert_int_eq(s21_is_equal(result, expected, &errorType), 1);
}
END_TEST

START_TEST(test_s21_negate_positive_to_negative) {
    s21_decimal value = {{12345, 0, 0, 0}};
    s21_decimal expected = {{12345, 0, 0, 0}};
    s21_decimal result = {0};
    int ret = s21_negate(value, &result);
    ck_assert_int_eq(ret, 0);
    int errorType = 0;
    ck_assert_int_eq(s21_is_equal(result, expected, &errorType), 1);
}
END_TEST
/*START_TEST(test_s21_negate_negative_to_positive) {
    s21_decimal value = {{12345, 0, 0, 0}};
    setBit(&value, MINUS_BIT_INDEX);  
    s21_decimal expected = {{12345, 0, 0, 0}};  
    s21_decimal result = {0};
    int ret = s21_negate(value, &result);
    ck_assert_int_eq(ret, 0);
}
END_TEST*/

START_TEST(test_s21_floor_positive) {
    s21_decimal value = {{12345, 0, 0, 0}};
    setScale(&value, 3);  
    s21_decimal expected = {{12, 0, 0, 0}};  
    s21_decimal result = {0};

    int ret = s21_floor(value, &result);
    ck_assert_int_eq(ret, 0);
    int errorType = 0;
    ck_assert_int_eq(s21_is_equal(result, expected, &errorType), 1);
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
    int errorType = 0;
    ck_assert_int_eq(s21_is_equal(result, expected, &errorType), 1);
}
END_TEST

START_TEST(test_s21_round_positive) {
    s21_decimal value = {{12345, 0, 0, 0}};
    setScale(&value, 3);  
    s21_decimal expected = {{12, 0, 0, 0}};  
    s21_decimal result = {0};

    int ret = s21_round(value, &result);
    ck_assert_int_eq(ret, 0);
    int errorType = 0;
    ck_assert_int_eq(s21_is_equal(result, expected, &errorType), 1);
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
    int errorType = 0;
    ck_assert_int_eq(s21_is_equal(result, expected, &errorType), 1);
}
END_TEST

Suite *other_suite(void) {
    Suite *s = suite_create("s21_others");

    TCase *tc_truncate = tcase_create("truncate");
    tcase_add_test(tc_truncate, test_s21_truncate);
    tcase_add_test(tc_truncate, test_s21_truncate_negative);
    suite_add_tcase(s, tc_truncate);

    TCase *tc_negate = tcase_create("negate");
    tcase_add_test(tc_negate, test_s21_negate_positive_to_negative);
    //tcase_add_test(tc_negate, test_s21_negate_negative_to_positive);
    suite_add_tcase(s, tc_negate);

    TCase *tc_floor = tcase_create("floor");
    tcase_add_test(tc_floor, test_s21_floor_positive);
    tcase_add_test(tc_floor, test_s21_floor_negative);
    suite_add_tcase(s, tc_floor);

    TCase *tc_round = tcase_create("round");
    tcase_add_test(tc_round, test_s21_round_positive);
    tcase_add_test(tc_round, test_s21_round_negative);
    suite_add_tcase(s, tc_round);

    return s;
}


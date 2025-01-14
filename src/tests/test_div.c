#include <check.h>
#include <stdio.h>

#include "../s21_decimal.h"

static s21_decimal num1[] = {
    {{0x0000000A, 0x00000000, 0x00000000, 0x00000000}},  // 0: 10
    {{0x0000000A, 0x00000000, 0x00000000, 0x00000000}},  // 1: 10
    {{0x000000B6, 0x00000000, 0x00000000, 0x00000000}},  // 2: 182
    {{0x0001F0F1, 0x00000000, 0x00000000, 0x00000000}},  // 3: 127217
    {{0x000000D4, 0x00000000, 0x00000000, 0x80000000}},  // 4: -212
    {{0x014CF9BF, 0x00000000, 0x00000000, 0x80020000}},  // 5: -218218.87
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 6: 0
    {{0x0001DC88, 0x00000000, 0x00000000, 0x00020000}},  // 7: 1219.92
};

static s21_decimal num2[] = {
    {{0x00000005, 0x00000000, 0x00000000, 0x00000000}},  // 0: 5
    {{0x00004E2A, 0x00000000, 0x00000000, 0x00000000}},  // 1: 20010
    {{0x00000065, 0x00000000, 0x00000000, 0x00000000}},  // 2: 101
    {{0x04FDBA54, 0x00000000, 0x00000000, 0x00000000}},  // 3: 83737172
    {{0x00000011, 0x00000000, 0x00000000, 0x80000000}},  // 4: -17
    {{0x9336DD9D, 0x00000032, 0x00000000, 0x80020000}},  // 5: -2172182112.29
    {{0x0000000A, 0x00000000, 0x00000000, 0x00000000}},  // 6: 10
    {{0x0116F341, 0x00000000, 0x00000000, 0x80030000}},  // 7: -18281.281
};

static s21_decimal expected_results[] = {
    {{0x00000002, 0x00000000, 0x00000000, 0x00000000}},  // 0: 2
    {{0x9BD58675, 0x15E87A6F, 0x00042243, 0x001C0000}},  // 1: 0.0004997501249375312343828086
    {{0x93F5DC83, 0xBC05DBBB, 0x3A39A17E, 0x001C0000}},  // 2: 1.8019801980198019801980198019
    {{0x32BBC140, 0x8D8AFA58, 0x000C911E, 0x001C0000}},  // 3: 0.0015192416576953422788149569
    {{0x89696969, 0xD80A02F7, 0x284B6DC6, 0x001B0000}},  // 4: 12.470588235294117647058823529
    {{0xADCFD4F0, 0xD696F916, 0x0000D4BB, 0x001C0000}},  // 5: 0.0001004606698330394895308016
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 6: 0
    {{0x9C29AC02, 0x8B157841, 0x0227FB71, 0x801C0000}},  // 7: -0.0667305535098990054362164227
};

START_TEST(test_s21_div_valid_cases) {
    for (size_t i = 0; i < sizeof(num1) / sizeof(s21_decimal); ++i) {
        s21_decimal result;
        int ret = s21_div(num1[i], num2[i], &result);
        ck_assert_int_eq(ret, 0);
        ck_assert_int_eq(result.bits[0], expected_results[i].bits[0]);
        ck_assert_int_eq(result.bits[1], expected_results[i].bits[1]);
        ck_assert_int_eq(result.bits[2], expected_results[i].bits[2]);
        ck_assert_int_eq(result.bits[3], expected_results[i].bits[3]);
    }
}
END_TEST

static s21_decimal error_cases_num1[] = {
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}},  // 0: max positive
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}},  // 1: max negative
};

static s21_decimal error_cases_num2[] = {
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0: division by zero
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 1: division by zero
};

static int error_expected_results[] = {
    1,  // Error: division by zero
    1,  // Error: division by zero
};

START_TEST(test_s21_div_error_cases) {
    for (size_t i = 0; i < sizeof(error_cases_num1) / sizeof(s21_decimal); ++i) {
        s21_decimal result;
        int ret = s21_div(error_cases_num1[i], error_cases_num2[i], &result);
        ck_assert_int_eq(ret, error_expected_results[i]);
    }
}
END_TEST

Suite *s21_decimal_suite(void) {
    Suite *s = suite_create("s21_decimal");
    TCase *tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_s21_div_valid_cases);
    tcase_add_test(tc_core, test_s21_div_error_cases);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s = s21_decimal_suite();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

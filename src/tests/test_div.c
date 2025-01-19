// #include <check.h>
// #include <stdio.h>

// #include "../s21_decimal.h"
// #include "test.h"

// s21_decimal dividend[] = {
//     // {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
//     // {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
//     // {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
//     {{0x0000000A, 0x00000000, 0x00000000, 0x00000000}},  // 10
//     // {{0x383c3983, 0x3c0e6d29, 0x0, 0x20000}},  // 43275163157541830.43
//     // {{0x760d7418, 0x49e39681, 0x2907c7,
//     //   0x80000000}},  // -49602691395915219137819672
//     // {{0x3d9, 0x0, 0x0, 0x80010000}},  // -10
//     // {{0xdc21, 0x0, 0x0, 0x20000}},    // 563.53

// };

// s21_decimal divisor[] = {
//     // {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
//     // {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
//     // {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
//     {{0x00000005, 0x00000000, 0x00000000, 0x00000000}},  // 5
//     // {{0x53ec8117, 0x220b2, 0x0, 0x0}},  // 598900237697303
//     // {{0x11cf5, 0x0, 0x0, 0x80000000}},  // -72949
//     // {{0x3, 0x0, 0x0, 0x80000000}},  // -3
//     // {{0x3e80ad, 0x0, 0x0, 0x80070000}},  // -0.4096173

// };

// s21_decimal result_array[] = {
//     // {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
//     // {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
//     // {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
//     {{0x00000002, 0x00000000, 0x00000000, 0x00000000}},  // 2
//     // {{0x66639e1e, 0x81794888, 0xe97a2e7d,
//     // 0x1b0000}},  // 72.257715782397174843307171358
//     // {{0x43f667d4, 0xbb33c640, 0xdbb54d10,
//     //   0x80000}},  // 679963966550812473616.08345556
//     // {{0xc1555555, 0x7f3dc7cf, 0x6a1718c6,
//     //   0x1b0000}},  // 3.33333333333333333333333333
//     // {{0xe7a1e95, 0x563569b8, 0x2c73eac5,
//     //   0x80190000}},  // -1375.7475575372426897008500373
// };

// int error_array[] = {ADD_OK, ADD_OK, DIVISION_BY_ZERO, ADD_OK,
//                      NUMBER_TOO_LARGE};

// START_TEST(div_1) {
//   size_t i = 0;
//   s21_decimal actual = {0}, expected = result_array[i];
//   for (; i < sizeof(dividend) / sizeof(s21_decimal); ++i) {
//     // int result = s21_div(dividend[i], divisor[i], &actual);
//     s21_div(dividend[i], divisor[i], &actual);
//     int row = ROW_NUMBER;
//     while (row--) {
//       if (expected.bits[row] != actual.bits[row]) {
//         printf("Error on row %d\n", row + 1);
//         printf("s21_div: Error on pair %ld\n", i + 1);
//       }
//     }
//     // ck_assert_int_eq(result, error_array[i]);
//   }
//   printf("((%x) (%x) (%x) (%x))\n", actual.bits[3], actual.bits[2],
//          actual.bits[1], actual.bits[0]);
// }
// END_TEST

// Suite *div_suite(void) {
//   Suite *s = suite_create("div_suite");
//   TCase *tc = tcase_create("div_suite");

//   if (s != NULL && tc != NULL) {
//     tcase_add_test(tc, div_1);
//     suite_add_tcase(s, tc);
//   }

//   return s;
// }
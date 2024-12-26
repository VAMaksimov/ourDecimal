#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <stdio.h>

#define bool _Bool
#define true 1
#define false 0

#ifndef NULL
#define NULL ((void *)0)
#endif

#define ROW_NUMBER 4
#define ADDITIONAL_INT_BIT 31
#define COLUMN_NUMBER 32
#define MINUS_BIT_INDEX 127

#define __INT_MIN__ -__INT32_MAX__ - 1
// #define isIntOutOfRange(x) !(x >= intUpperBorder && x <= intLowerBorder)

#define __FLT_MIN__ -__FLT_MAX__ - 1
// #define isFloatOutOfRange(x) !(x >= floatUpperBorder && x <=
// floatLowerBorder)

#define abs(x) ((x) < 0 ? -(x) : (x))
#define getRow(x) (x / COLUMN_NUMBER) % ROW_NUMBER
#define getColumn(x) (x % COLUMN_NUMBER)

typedef struct {
  int bits[4];
} s21_decimal;

void nullOut(s21_decimal *dst);
bool isSetBit(s21_decimal number, int index);
void setBit(s21_decimal *dst, int index);
void inverseBit(s21_decimal *dst, int index);
void resetBit(s21_decimal *dst, int index);

/**
 * @brief convert int to decimal
 * @param src int value
 * @param dst pointer to the decimal structure
 */
int s21_from_int_to_decimal(int src, s21_decimal *dst);

/**
 * @brief convert decimal to int
 * @param src decimal value
 * @param dst pointer to the int structure
 */
int s21_from_decimal_to_int(s21_decimal src, int *dst);

#endif  // S21_DECIMAL_H

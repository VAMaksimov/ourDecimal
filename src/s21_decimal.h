#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#define bool _Bool
#define true 1
#define false 0

#define CONVERTATION_SUCCESS 0
#define CONVERTATION_ERROR 1

#ifndef NULL
#define NULL ((void *)0)
#endif

typedef struct {
  int bits[4];
} s21_decimal;

#define ROW_NUMBER sizeof(s21_decimal) / sizeof(int)
#define COLUMN_NUMBER sizeof(int) * 8
#define ADDITIONAL_INT_BIT (3 * COLUMN_NUMBER - 1)
#define MINUS_BIT_INDEX (ROW_NUMBER * COLUMN_NUMBER - 1)

// #define __INT_MIN__ -2147483648
#define __INT_MIN__ 0x80000000

#define abs(x) ((x) < 0 ? -(x) : (x))
#define getRow(x) (x / COLUMN_NUMBER) % ROW_NUMBER
#define getColumn(x) (x % COLUMN_NUMBER)

void nullOutDecimal(s21_decimal *dst);
void negateDecimal(s21_decimal *dst);
bool isSetBit(s21_decimal number, int index);
void setBit(s21_decimal *dst, int index);
void inverseBit(s21_decimal *dst, int index);
void resetBit(s21_decimal *dst, int index);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);

#endif  // S21_DECIMAL_H

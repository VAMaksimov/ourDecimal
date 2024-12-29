#include "../s21_decimal.h"
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == NULL || !isCorrectDecimal(&value_1) ||
      !isCorrectDecimal(&value_2))
    return NUMBER_TOO_SMALL;

  int errrorType = ADD_OK;

  alignScale(&value_1, &value_2, &errrorType);
}

s21_long_decimal addition(s21_long_decimal a, s21_long_decimal b,
                          s21_long_decimal *result) {
  unsigned carry = 0;
  nullOutLongDecimal(result);

  for (int bit_index = 0; bit_index < VALUE_PART_SIZE; bit_index++) {
    int bit1 = isSetLongBit(a, bit_index) ? 1 : 0;
    int bit2 = isSetLongBit(b, bit_index) ? 1 : 0;
    int sum = bit1 + bit2 + carry;

    int result_bit = sum % 2;

    if (result_bit)
      setLongBit(result, bit_index);
    else
      resetLongBit(result, bit_index);

    carry = sum / 2;
  }
  return *result;
}

s21_long_decimal subtraction(s21_long_decimal a, s21_long_decimal b,
                             s21_long_decimal *result) {
  unsigned borrow = 0;
  nullOutLongDecimal(result);

  for (int bit_index = 0; bit_index < VALUE_PART_SIZE; bit_index++) {
    int bit1 = isSetLongBit(a, bit_index) ? 1 : 0;
    int bit2 = isSetLongBit(b, bit_index) ? 1 : 0;
    int diff = bit1 - bit2 - borrow;

    int result_bit = diff % 2;
    if (result_bit < 0) result_bit += 2;

    if (result_bit)
      setLongBit(result, bit_index);
    else
      resetLongBit(result, bit_index);

    borrow = diff < 0;
  }
  return *result;
}
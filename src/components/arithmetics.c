#include "../s21_decimal.h"

s21_long_decimal addition(s21_decimal a, s21_decimal b,
                          s21_long_decimal *result) {
  unsigned carry = 0;
  nullOutLongDecimal(result);
  for (int i = 0; i < 96; i++) {
    int bit1 = isSetBit(a, i);
    int bit2 = isSetBit(b, i);

    int sum = bit1 + bit2 + carry;

    int result_bit = sum % 2;

    if (result_bit)
      setLongBit(result, i);
    else
      resetLongBit(result, i);

    carry = sum / 2;
  }
  return *result;
}

s21_long_decimal subtraction(s21_decimal a, s21_decimal b,
                             s21_long_decimal *result) {
  unsigned borrow = 0;
  nullOutLongDecimal(result);

  for (int i = 0; i < 96; i++) {
    int bit1 = isSetBit(a, i);
    int bit2 = isSetBit(b, i);

    int diff = bit1 - bit2 - borrow;

    int result_bit = diff % 2;
    if (result_bit < 0) result_bit += 2;

    if (result_bit)
      setLongBit(result, i);
    else
      resetLongBit(result, i);

    borrow = diff < 0;
  }

  return *result;
}
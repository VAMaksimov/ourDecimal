#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  return addWrapper(value_1, value_2, result, addition, subtraction);
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  inverseBit(&value_2, MINUS_BIT_INDEX);
  return addWrapper(value_1, value_2, result, addition, subtraction);
}

int addWrapper(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
               void (*primaryFunction)(s21_decimal value_1, s21_decimal value_2,
                                       s21_decimal *result, int *errorType),
               void (*secondaryFunction)(s21_decimal value_1,
                                         s21_decimal value_2,
                                         s21_decimal *result, int *errorType)) {
  if (result == NULL || !isCorrectDecimal(&value_1) ||
      !isCorrectDecimal(&value_2))
    return NUMBER_TOO_SMALL;

  int errorType = ADD_OK;

  alignScale(&value_1, &value_2, &errorType);

  if (errorType == ADD_OK) {
    setScale(result, max(getScale(value_1), getScale(value_2)));

    if (isSetBit(value_1, MINUS_BIT_INDEX) ==
        isSetBit(value_2, MINUS_BIT_INDEX))
      primaryFunction(value_1, value_2, result, &errorType);
    else
      secondaryFunction(value_1, value_2, result, &errorType);

    if (isIntPartBigger(value_1, value_2))
      copySign(value_1, result);
    else
      copySign(value_2, result);
  }
  if (errorType) resetDecimal(result);
  return errorType;
}

// s21_long_decimal addition(s21_long_decimal a, s21_long_decimal b,
//                           s21_long_decimal *result) {
//   unsigned carry = 0;
//   nullOutLongDecimal(result);

//   for (int bit_index = 0; bit_index < VALUE_PART_SIZE; bit_index++) {
//     int bit1 = isSetLongBit(a, bit_index) ? 1 : 0;
//     int bit2 = isSetLongBit(b, bit_index) ? 1 : 0;
//     int sum = bit1 + bit2 + carry;

//     int result_bit = sum % 2;

//     if (result_bit)
//       setLongBit(result, bit_index);
//     else
//       resetLongBit(result, bit_index);

//     carry = sum / 2;
//   }
//   return *result;
// }

void addition(s21_decimal a, s21_decimal b, s21_decimal *result,
              int *errorType) {
  unsigned carry = 0;
  nullOutDecimal(result);

  for (int bit_index = 0; bit_index < VALUE_PART_SIZE; bit_index++) {
    int bit1 = isSetBit(a, bit_index) ? 1 : 0;
    int bit2 = isSetBit(b, bit_index) ? 1 : 0;
    int sum = bit1 + bit2 + carry;

    int result_bit = sum % 2;

    if (result_bit)
      setBit(result, bit_index);
    else
      resetBit(result, bit_index);

    carry = sum / 2;
  }
  if (carry) {
    if (isSetBit(a, MINUS_BIT_INDEX))
      *errorType = NUMBER_TOO_SMALL;
    else
      *errorType = NUMBER_TOO_LARGE;
  }
}

// s21_long_decimal subtraction(s21_long_decimal a, s21_long_decimal b,
//                              s21_long_decimal *result) {
//   unsigned borrow = 0;
//   nullOutLongDecimal(result);

//   for (int bit_index = 0; bit_index < VALUE_PART_SIZE; bit_index++) {
//     int bit1 = isSetLongBit(a, bit_index) ? 1 : 0;
//     int bit2 = isSetLongBit(b, bit_index) ? 1 : 0;
//     int diff = bit1 - bit2 - borrow;

//     int result_bit = diff % 2;
//     if (result_bit < 0) result_bit += 2;

//     if (result_bit)
//       setLongBit(result, bit_index);
//     else
//       resetLongBit(result, bit_index);

//     borrow = diff < 0;
//   }
//   return *result;
// }

void subtraction(s21_decimal a, s21_decimal b, s21_decimal *result,
                 int *errorType) {
  unsigned borrow = 0;
  nullOutDecimal(result);

  for (int bit_index = 0; bit_index < VALUE_PART_SIZE; bit_index++) {
    int bit1 = isSetBit(a, bit_index) ? 1 : 0;
    int bit2 = isSetBit(b, bit_index) ? 1 : 0;
    int diff = bit1 - bit2 - borrow;

    int result_bit = diff % 2;
    if (result_bit < 0) result_bit += 2;

    if (result_bit)
      setBit(result, bit_index);
    else
      resetBit(result, bit_index);

    borrow = diff < 0;
  }
  if (borrow) {
    if (isSetBit(a, MINUS_BIT_INDEX))
      *errorType = NUMBER_TOO_SMALL;
    else
      *errorType = NUMBER_TOO_LARGE;
  }
}

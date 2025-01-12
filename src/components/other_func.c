#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
    if (result == NULL || !isCorrectDecimal(&value)) return 1;
    int exp = getScale(value);
    int sign = isSetBit(value, MINUS_BIT_INDEX);
    *result = value;
    s21_decimal ten = {0};
    ten.bits[0] = 10;
    ten.bits[1] = ten.bits[2] = ten.bits[3] = 0;
    setScale(&ten, 0);
    while (exp > 0) {
        int errorType = 0;
        if (s21_div(*result, ten, result) != 0) return 1;
        exp--;
    }
    setScale(result, 0);
    if (sign) setBit(result, MINUS_BIT_INDEX);
    return 0;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
    if (result == NULL || !isCorrectDecimal(&value)) return 1;
    *result = value;
    if (isSetBit(value, MINUS_BIT_INDEX)) {
        resetBit(result, MINUS_BIT_INDEX);
    } else {
        setBit(result, MINUS_BIT_INDEX);
    }  
    return 0;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
    if (result == NULL || !isCorrectDecimal(&value)) return 1;
    *result = value;
    int scale = getScale(value);
    if (scale > 0) {
        s21_decimal truncated = {0};
        s21_truncate(value, &truncated);
        s21_decimal fractional_part = {0};
        s21_sub(value, truncated, &fractional_part);
        if (isSetBit(value, MINUS_BIT_INDEX) && !isDecimalZero(fractional_part)) {
            s21_decimal one = {0};
            one.bits[0] = 1;
            s21_sub(truncated, one, result);
        } else {
            *result = truncated;
        }
    }
    return 0;
}

int s21_round(s21_decimal value, s21_decimal *result) {
    if (result == NULL || !isCorrectDecimal(&value)) return 1;
    *result = value;
    int scale = getScale(value);
    if (scale > 0) {
        s21_decimal truncated = {0};
        s21_truncate(value, &truncated);

        s21_decimal fractional_part = {0};
        s21_sub(value, truncated, &fractional_part);

        s21_decimal half = {0};
        half.bits[0] = 5;
        setScale(&half, scale);

        if (is_greater_or_equal(fractional_part, half, NULL)) {
            s21_decimal one = {0};
            one.bits[0] = 1;
            if (!isSetBit(value, MINUS_BIT_INDEX)) {
                s21_add(truncated, one, result);
            } else {
                s21_sub(truncated, one, result);
            }
        } else {
            *result = truncated;
        }
    }
    return 0;
}
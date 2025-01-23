#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == NULL) return CONVERTATION_ERROR;

  resetDecimal(dst);
  dst->bits[0] = abs(src);
  resetBit(dst, ADDITIONAL_INT_BIT);
  if (src < 0) setBit(dst, MINUS_BIT_INDEX);

  return CONVERTATION_SUCCESS;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (dst == NULL || src.bits[1] || src.bits[2] ||
      isSetBit(src, ADDITIONAL_INT_BIT) || !isCorrectDecimal(&src))
    return CONVERTATION_ERROR;
  s21_decimal truncated = src;
  *dst = src.bits[0];
  if (isSetBit(src, MINUS_BIT_INDEX)) {
    *dst = -*dst;
  }
  if (isScaleSet(src)) {
    s21_truncate(src, &truncated);
    *dst = truncated.bits[0];
  }
  return CONVERTATION_SUCCESS;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (!dst || (abs(src) > 0 && abs(src) < 1e-28) ||
      (abs(src) > 7.9228162514264337593543950335e+28 || isinf(src))) {
    return CONVERTATION_ERROR;
  }
  int exp = getFloatExp(&src);
  resetDecimal(dst);
  int sign = 0;
  if (src < 0) {
    src *= -1;
    sign = 1;
    setNegativeSign(dst, 1);
  }
  double tmp = (double)src;
  int scale = 0;
  while (scale < 28 && (int)tmp / (int)pow(2, 21) == 0) {
    tmp *= 10;
    scale++;
  }

  if (scale <= 28 && (exp > -94 && exp < 96)) {
    fbits mant;
    tmp = (float)tmp;
    for (; fmod(tmp, 10) == 0 && scale > 0; scale--) {
      tmp /= 10;
    }
    mant.fl = tmp;
    exp = getFloatExp(&mant.fl);
    setBitFloat(dst, exp, 1);
    for (int i = exp - 1, j = 22; j >= 0; i--, j--) {
      if ((mant.ui & (1 << j)) != 0) {
        setBitFloat(dst, i, 1);
      }
    }

    setScale(dst, scale);
    if (sign) {
      setNegativeSign(dst, 1);
    }
  }

  return CONVERTATION_SUCCESS;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (dst == NULL || src.bits[1] || src.bits[2] || !isCorrectDecimal(&src))
    return CONVERTATION_ERROR;

  double tmp = 0;
  int exp = 0;
  for (int i = 0; i < VALUE_PART_SIZE; i++) {
    if (isSetBit(src, i)) tmp += pow(2, i);
  }
  if ((exp = getScale(src)) > 0) {
    for (int i = exp; i > 0; i--) tmp /= 10.0;
  }
  *dst = (float)tmp;
  if (isSetBit(src, MINUS_BIT_INDEX)) {
    *dst *= -1;
  }
  int errorType = CONVERTATION_SUCCESS;
  if (fabs(*dst) > 7.9228162514264337593543950335e+28 || isinf(*dst)) {
    errorType = CONVERTATION_ERROR;
  }

  return errorType;
}

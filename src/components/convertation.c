#include "../s21_decimal.h"

/**
 * @brief convert int to decimal
 * @param src int value
 * @param dst pointer to the decimal structure
 */
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == NULL) return CONVERTATION_ERROR;

  resetDecimal(dst);
  dst->bits[0] = abs(src);
  resetBit(dst, ADDITIONAL_INT_BIT);
  if (src < 0) setBit(dst, MINUS_BIT_INDEX);

  return CONVERTATION_SUCCESS;
}

/**
 * @brief converts decimal to int
 * @param src decimal value
 * @param dst pointer to the int structure
 */
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
  if (!dst) {
    return CONVERTATION_ERROR;
  }
  if (abs(src) > 0 && abs(src) < 1e-28) {
    return CONVERTATION_ERROR;
  }
  if (abs(src) > 7.9228162514264337593543950335e+28 || isinf(src)) {
    return CONVERTATION_ERROR;
  }
  if (src < 0) {
    setBit(dst, MINUS_BIT_INDEX);
  }
  nullOutDecimal(dst);

  char float_str[64];
  sprintf(float_str, "%.7E", fabsf(src));

  int exp = getFloatExponent(float_str);

  char int_str[64] = {0};
  int scale = 0;
  int stop = 0;
  for (char *p = float_str; *p != 'E'; p++) {
    if (*p != '.') {
      strncat(int_str, p, 1);
    } else {
      scale = strlen(p + 1);
    }
  }
  scale = scale - exp;
  if (scale < 0 || scale > 28) return CONVERTATION_ERROR;

  int lenght = strlen(int_str);
  int part_index = 0;
  int parts[3] = {0};

  while (lenght > 0 && part_index <= 2) {
    int start = (lenght > 10) ? (lenght - 10) : 0;
    char part_str[11] = {0};
    strncpy(part_str, &int_str[start], lenght - start);
    parts[part_index] = atoi(part_str);
    part_index++;
    lenght -= 10;
  }
  dst->bits[0] = parts[0];
  dst->bits[1] = parts[1];
  dst->bits[2] = parts[2];

  setScale(dst, scale);

  return CONVERTATION_SUCCESS;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (!dst) {
    return CONVERTATION_ERROR;
  }
  if (fabs(*dst) > 0 && fabs(*dst) < 1e-28) {
    return CONVERTATION_ERROR;
  }
  if (fabs(*dst) > 7.9228162514264337593543950335e+28 || isinf(*dst)) {
    return CONVERTATION_ERROR;
  }
  int scale = getScale(src);
  int num[3] = {0};

  for (int i = 0; i < 3; i++) {
    num[i] = src.bits[i];
  }
  float result = 0.0;
  result += (long long)num[0];
  result += (long long)num[1] << 32;
  result += (long long)num[2] << 32;

  for (int i = 0; i < scale; i++) {
    result /= 10.0;
  }
  if (isSetBit(src, MINUS_BIT_INDEX)) {
    result = -result;
  }
  *dst = result;
  return CONVERTATION_SUCCESS;
}
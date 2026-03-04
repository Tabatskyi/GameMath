#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// 1)
uint32_t float_to_bits(float value); // (a)
uint64_t double_to_bits(double value); 

float  bits_to_float(uint32_t bits); // (b)
double bits_to_double(uint64_t bits);

// 2)
typedef enum FPClass : int {
    FP_CLASS_NAN = 0,
    FP_CLASS_INFINITE = 1,
    FP_CLASS_ZERO = 2,
    FP_CLASS_SUBNORMAL = 3,
    FP_CLASS_NORMAL = 4
} FPClass;

bool float_is_finite(float value); // (a)
bool double_is_finite(double value);

bool float_is_inf(float value); // (b)
bool double_is_inf(double value);

bool float_is_positive_inf(float value); // (c)
bool double_is_positive_inf(double value);

bool float_is_negative_inf(float value); // (d)
bool double_is_negative_inf(double value);

bool float_is_zero(float value); // (e)
bool double_is_zero(double value);

bool float_is_positive_zero(float value); // (f)
bool double_is_positive_zero(double value);

bool float_is_negative_zero(float value); // (g)
bool double_is_negative_zero(double value);

bool float_is_nan(float value); // (h)
bool double_is_nan(double value);

bool float_is_normal(float value); // (i)
bool double_is_normal(double value);

bool float_is_subnormal(float value); // (j)
bool double_is_subnormal(double value);

bool float_is_signed(float value); // (k)
bool double_is_signed(double value);

FPClass float_classify(float value); // (l)
FPClass double_classify(double value);

// 3)
float  float_abs(float value); // (a)
double double_abs(double value);

float  float_min(float a, float b); // (b)
double double_min(double a, double b);

float  float_max(float a, float b); // (c)
double double_max(double a, double b); 

float  float_clamp(float value, float lo, float hi); // (d)
double double_clamp(double value, double lo, double hi);

// 4)
bool float_equal_eps(float a, float b, float eps); // (a)
bool double_equal_eps(double a, double b, double eps);

bool float_equal(float a, float b); // (b)
bool double_equal(double a, double b); 

bool float_less_eps(float a, float b, float eps); // (c)
bool double_less_eps(double a, double b, double eps);

bool float_less(float a, float b); // (d)
bool double_less(double a, double b);

bool float_greater_eps(float a, float b, float eps); // (e)
bool double_greater_eps(double a, double b, double eps);

bool float_greater(float a, float b); // (f)
bool double_greater(double a, double b);

#ifdef __cplusplus
}
#endif
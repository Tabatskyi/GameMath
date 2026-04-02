#include "Homework1.h"

// float : [s|eeeeeeee|mmmmmmmmmmmmmmmmmmmmmmm] (1+8+23 = 32 bits)
// double: [s|eeeeeeeeeee|mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm] (1+11+52 = 64 bits)

// 1)
// (a)
uint32_t float_to_bits(float value)
{
    uint32_t bits = {0};
    memcpy(&bits, &value, sizeof bits);
    return bits;
}

// (b)
uint64_t double_to_bits(double value)
{
    uint64_t bits = {0};
    memcpy(&bits, &value, sizeof bits);
    return bits;
}

// 1b) Inverse of the above: reconstruct a float from its raw bit pattern.
float bits_to_float(uint32_t bits)
{
    float value = {0};
    memcpy(&value, &bits, sizeof value);
    return value;
}

double bits_to_double(uint64_t bits)
{
    double value = {0};
    memcpy(&value, &bits, sizeof value);
    return value;
}

// 2)

static const uint32_t F32_SIGN_MASK = 0b1'00000000'00000000000000000000000u;
static const uint32_t F32_EXP_MASK  = 0b0'11111111'00000000000000000000000u;
static const uint32_t F32_MAN_MASK  = 0b0'00000000'11111111111111111111111u;

static const uint64_t F64_SIGN_MASK = 0b1'00000000000'0000000000000000000000000000000000000000000000000000ull;
static const uint64_t F64_EXP_MASK  = 0b0'11111111111'0000000000000000000000000000000000000000000000000000ull;
static const uint64_t F64_MAN_MASK  = 0b0'00000000000'1111111111111111111111111111111111111111111111111111ull;

// (a) 
bool float_is_finite(float value)
{
    uint32_t bits = float_to_bits(value);
    return (bits & F32_EXP_MASK) != F32_EXP_MASK;
}

bool double_is_finite(double value)
{
    uint64_t bits = double_to_bits(value);
    return (bits & F64_EXP_MASK) != F64_EXP_MASK;
}

// (b)
bool float_is_inf(float value)
{
    uint32_t bits = float_to_bits(value);
    return (bits & F32_EXP_MASK) == F32_EXP_MASK
        && (bits & F32_MAN_MASK) == 0;
}

bool double_is_inf(double value)
{
    uint64_t bits = double_to_bits(value);
    return (bits & F64_EXP_MASK) == F64_EXP_MASK
        && (bits & F64_MAN_MASK) == 0;
}

// (c) 
bool float_is_positive_inf(float value)
{
    return float_to_bits(value) == (F32_EXP_MASK);
}

bool double_is_positive_inf(double value)
{
    return double_to_bits(value) == (F64_EXP_MASK);
}

// (d) 
bool float_is_negative_inf(float value)
{
    return float_to_bits(value) == (F32_SIGN_MASK | F32_EXP_MASK);
}

bool double_is_negative_inf(double value)
{
    return double_to_bits(value) == (F64_SIGN_MASK | F64_EXP_MASK);
}

// (e)
bool float_is_zero(float value)
{
    uint32_t bits = float_to_bits(value);
    return (bits & ~F32_SIGN_MASK) == 0;
}

bool double_is_zero(double value)
{
    uint64_t bits = double_to_bits(value);
    return (bits & ~F64_SIGN_MASK) == 0;
}

// (f)
bool float_is_positive_zero(float value)
{
    return float_to_bits(value) == 0u;
}

bool double_is_positive_zero(double value)
{
    return double_to_bits(value) == 0ull;
}

// (g) 
bool float_is_negative_zero(float value)
{
    return float_to_bits(value) == F32_SIGN_MASK;
}

bool double_is_negative_zero(double value)
{
    return double_to_bits(value) == F64_SIGN_MASK;
}

// (h) 
bool float_is_nan(float value)
{
    uint32_t bits = float_to_bits(value);
    return (bits & F32_EXP_MASK) == F32_EXP_MASK
        && (bits & F32_MAN_MASK) != 0;
}

bool double_is_nan(double value)
{
    uint64_t bits = double_to_bits(value);
    return (bits & F64_EXP_MASK) == F64_EXP_MASK
        && (bits & F64_MAN_MASK) != 0;
}

// (i) 
bool float_is_normal(float value)
{
    uint32_t exp = float_to_bits(value) & F32_EXP_MASK;
    return exp != 0 && exp != F32_EXP_MASK;
}

bool double_is_normal(double value)
{
    uint64_t exp = double_to_bits(value) & F64_EXP_MASK;
    return exp != 0 && exp != F64_EXP_MASK;
}

// (j) 
bool float_is_subnormal(float value)
{
    uint32_t bits = float_to_bits(value);
    return (bits & F32_EXP_MASK) == 0
        && (bits & F32_MAN_MASK) != 0;
}

bool double_is_subnormal(double value)
{
    uint64_t bits = double_to_bits(value);
    return (bits & F64_EXP_MASK) == 0
        && (bits & F64_MAN_MASK) != 0;
}

// (k) 
bool float_is_signed(float value)
{
    return (float_to_bits(value) & F32_SIGN_MASK) != 0;
}

bool double_is_signed(double value)
{
    return (double_to_bits(value) & F64_SIGN_MASK) != 0;
}

// (l) 
FPClass float_classify(float value)
{
    if (float_is_nan(value)) return FP_CLASS_NAN;
    if (float_is_inf(value)) return FP_CLASS_INFINITE;
    if (float_is_zero(value)) return FP_CLASS_ZERO;
    if (float_is_subnormal(value)) return FP_CLASS_SUBNORMAL;
    return FP_CLASS_NORMAL;
}

FPClass double_classify(double value)
{
    if (double_is_nan(value)) return FP_CLASS_NAN;
    if (double_is_inf(value)) return FP_CLASS_INFINITE;
    if (double_is_zero(value)) return FP_CLASS_ZERO;
    if (double_is_subnormal(value)) return FP_CLASS_SUBNORMAL;
    return FP_CLASS_NORMAL;
}

// 3)

// (a) 
float float_abs(float value)
{
    return bits_to_float(float_to_bits(value) & ~F32_SIGN_MASK);
}

double double_abs(double value)
{
    return bits_to_double(double_to_bits(value) & ~F64_SIGN_MASK);
}

// (b)
float float_min(float a, float b)
{
    if (float_is_nan(a)) return b;
    if (float_is_nan(b)) return a;
    if (float_is_zero(a) && float_is_zero(b))
        return float_is_signed(a) ? a : b;
    return a < b ? a : b;
}

double double_min(double a, double b)
{
    if (double_is_nan(a)) return b;
    if (double_is_nan(b)) return a;
    if (double_is_zero(a) && double_is_zero(b))
        return double_is_signed(a) ? a : b;
    return a < b ? a : b;
}

// (c)
float float_max(float a, float b)
{
    if (float_is_nan(a)) return b;
    if (float_is_nan(b)) return a;
    if (float_is_zero(a) && float_is_zero(b))
        return float_is_signed(a) ? b : a;
    return a > b ? a : b;
}

double double_max(double a, double b)
{
    if (double_is_nan(a)) return b;
    if (double_is_nan(b)) return a;
    if (double_is_zero(a) && double_is_zero(b))
        return double_is_signed(a) ? b : a;
    return a > b ? a : b;
}

// (d) 
float float_clamp(float value, float low, float high)
{
    return float_min(float_max(value, low), high);
}

double double_clamp(double value, double low, double high)
{
    return double_min(double_max(value, low), high);
}

// 4)
static int32_t f32_to_ordered(float value)
{
    int32_t i = {0};
    memcpy(&i, &value, sizeof i);
    if (i < 0)
        i = (int32_t)(0x80000000u - (uint32_t)i);
    return i;
}

static int64_t f64_to_ordered(double value)
{
    int64_t i = {0};
    memcpy(&i, &value, sizeof i);
    if (i < 0)
        i = (int64_t)(0x8000000000000000ull - (uint64_t)i);
    return i;
}

// Max distance treated as equal
static const int32_t F32_MAX_ULP = 4;
static const int64_t F64_MAX_ULP = 4;

// (a) 
bool float_equal_eps(float a, float b, float eps)
{
    if (float_is_nan(a) || float_is_nan(b)) return false;
    return float_abs(a - b) <= eps;
}

bool double_equal_eps(double a, double b, double eps)
{
    if (double_is_nan(a) || double_is_nan(b)) return false;
    return double_abs(a - b) <= eps;
}

// (b)
bool float_equal(float a, float b)
{
    if (float_is_nan(a) || float_is_nan(b)) return false;
    int64_t diff = (int64_t)f32_to_ordered(a) - (int64_t)f32_to_ordered(b);
    if (diff < 0) diff = -diff;
    return diff <= F32_MAX_ULP;
}

bool double_equal(double a, double b)
{
    if (double_is_nan(a) || double_is_nan(b)) return false;
    __int128 diff = (__int128)f64_to_ordered(a) - (__int128)f64_to_ordered(b);
    if (diff < 0) diff = -diff;
    return diff <= F64_MAX_ULP;
}

// (c) 
bool float_less_eps(float a, float b, float eps)
{
    if (float_is_nan(a) || float_is_nan(b)) return false;
    return b - a > eps;
}

bool double_less_eps(double a, double b, double eps)
{
    if (double_is_nan(a) || double_is_nan(b)) return false;
    return b - a > eps;
}

// (d) 
bool float_less(float a, float b)
{
    if (float_is_nan(a) || float_is_nan(b)) return false;
    return a < b;
}

bool double_less(double a, double b)
{
    if (double_is_nan(a) || double_is_nan(b)) return false;
    return a < b;
}

// (e)  
bool float_greater_eps(float a, float b, float eps)
{
    if (float_is_nan(a) || float_is_nan(b)) return false;
    return a - b > eps;
}

bool double_greater_eps(double a, double b, double eps)
{
    if (double_is_nan(a) || double_is_nan(b)) return false;
    return a - b > eps;
}

// (f) 
bool float_greater(float a, float b)
{
    if (float_is_nan(a) || float_is_nan(b)) return false;
    return a > b;
}

bool double_greater(double a, double b)
{
    if (double_is_nan(a) || double_is_nan(b)) return false;
    return a > b;
}

// int main(void)
// {
//     printf("%.1000f\n", bits_to_double(0b1'01110110'011100101011001100110010010ull));
//     printf("%.1000f\n", bits_to_double(0b1'00000000'011100000000000000000000000ull));
//     return 0;
// }
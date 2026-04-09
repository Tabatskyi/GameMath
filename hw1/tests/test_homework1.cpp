#include "../hw1.h"

#include <gtest/gtest.h>
#include <cmath>
#include <cstdint>
#include <limits>

// IEEE 754 float layout  (32 bits): [s|eeeeeeee|mmmmmmmmmmmmmmmmmmmmmmm]
// IEEE 754 double layout (64 bits): [s|eeeeeeeeeee|mmmm...mmmm] (52 m-bits)
// Digit separator ' groups the three fields so the structure is visible directly.

// 1)
// (a) float_to_bits
TEST(FloatToBits, PositiveZero) {
    EXPECT_EQ(float_to_bits(0.0f), 0b0'00000000'00000000000000000000000u);
}

TEST(FloatToBits, NegativeZero) {
    EXPECT_EQ(float_to_bits(-0.0f), 0b1'00000000'00000000000000000000000u);
}

TEST(FloatToBits, One) {
    // Biased exponent = 127 , mantissa = 0 -> value = 1.0 * 2^(127-127)
    EXPECT_EQ(float_to_bits(1.0f), 0b0'01111111'00000000000000000000000u);
}

TEST(FloatToBits, NegativeOne) {
    EXPECT_EQ(float_to_bits(-1.0f), 0b1'01111111'00000000000000000000000u);
}

TEST(FloatToBits, PositiveInfinity) {
    // Exponent all-ones, mantissa zero
    EXPECT_EQ(float_to_bits(HUGE_VALF), 0b0'11111111'00000000000000000000000u);
}

TEST(FloatToBits, NegativeInfinity) {
    EXPECT_EQ(float_to_bits(-HUGE_VALF), 0b1'11111111'00000000000000000000000u);
}

TEST(FloatToBits, NaN) {
    // NaN: exponent all-ones AND mantissa non-zero
    const uint32_t bits = float_to_bits(std::numeric_limits<float>::quiet_NaN());
    constexpr uint32_t EXP_MASK = 0b0'11111111'00000000000000000000000u;
    constexpr uint32_t MAN_MASK = 0b0'00000000'11111111111111111111111u;
    EXPECT_EQ(bits & EXP_MASK, EXP_MASK); // exponent must be all-ones
    EXPECT_NE(bits & MAN_MASK, 0u); // mantissa must be non-zero
}

// double_to_bits
TEST(DoubleToBits, PositiveZero) {
    EXPECT_EQ(double_to_bits(0.0), 0b0'00000000000'0000000000000000000000000000000000000000000000000000ull);
}

TEST(DoubleToBits, NegativeZero) {
    EXPECT_EQ(double_to_bits(-0.0), 0b1'00000000000'0000000000000000000000000000000000000000000000000000ull);
}

TEST(DoubleToBits, One) {
    // Biased exponent = 1023 (01111111111), mantissa = 0 value = 1.0 * 2^(1023-1023)
    EXPECT_EQ(double_to_bits(1.0), 0b0'01111111111'0000000000000000000000000000000000000000000000000000ull);
}

TEST(DoubleToBits, NegativeOne) {
    EXPECT_EQ(double_to_bits(-1.0), 0b1'01111111111'0000000000000000000000000000000000000000000000000000ull);
}

TEST(DoubleToBits, PositiveInfinity) {
    EXPECT_EQ(double_to_bits(HUGE_VAL), 0b0'11111111111'0000000000000000000000000000000000000000000000000000ull);
}

TEST(DoubleToBits, NegativeInfinity) {
    EXPECT_EQ(double_to_bits(-HUGE_VAL), 0b1'11111111111'0000000000000000000000000000000000000000000000000000ull);
}

TEST(DoubleToBits, NaN) {
    const uint64_t bits = double_to_bits(std::numeric_limits<double>::quiet_NaN());
    constexpr uint64_t EXP_MASK = 0b0'11111111111'0000000000000000000000000000000000000000000000000000ull;
    constexpr uint64_t MAN_MASK = 0b0'00000000000'1111111111111111111111111111111111111111111111111111ull;
    EXPECT_EQ(bits & EXP_MASK, EXP_MASK);
    EXPECT_NE(bits & MAN_MASK, 0ull);
}

// Shared values
static constexpr float F_NORMAL = 1.0f;
static constexpr float F_NEG = -1.0f;
static constexpr float F_POS_INF = HUGE_VALF;
static constexpr float F_NEG_INF = -HUGE_VALF;
static constexpr float F_POS_ZERO = 0.0f;
static constexpr float F_NEG_ZERO = -0.0f;
static const float F_NAN = std::numeric_limits<float>::quiet_NaN();
static const float F_SUBNORMAL = std::numeric_limits<float>::denorm_min();

static constexpr double D_NORMAL = 1.0;
static constexpr double D_NEG = -1.0;
static constexpr double D_POS_INF = HUGE_VAL;
static constexpr double D_NEG_INF = -HUGE_VAL;
static constexpr double D_POS_ZERO = 0.0;
static constexpr double D_NEG_ZERO = -0.0;
static const double D_NAN = std::numeric_limits<double>::quiet_NaN();
static const double D_SUBNORMAL = std::numeric_limits<double>::denorm_min();

// (b) bits_to_float
TEST(BitsToFloat, RoundTripOne) { 
    EXPECT_EQ(float_to_bits(bits_to_float(float_to_bits(1.0f))),
    float_to_bits(1.0f)); 
}

TEST(BitsToFloat, RoundTripNegZero) { 
    EXPECT_EQ(float_to_bits(bits_to_float(float_to_bits(-0.0f))), 
    float_to_bits(-0.0f)); 
}

TEST(BitsToFloat, RoundTripInf) { 
    EXPECT_EQ(float_to_bits(bits_to_float(float_to_bits(F_POS_INF))), 
    float_to_bits(F_POS_INF)); 
}

TEST(BitsToFloat, RoundTripNaN) { 
    EXPECT_EQ(float_to_bits(bits_to_float(float_to_bits(F_NAN))), 
    float_to_bits(F_NAN)); 
}

// bits_to_double
TEST(BitsToDouble, RoundTripOne) { 
    EXPECT_EQ(double_to_bits(bits_to_double(double_to_bits(1.0))), 
    double_to_bits(1.0)); 
}

TEST(BitsToDouble, RoundTripNegZero) { 
    EXPECT_EQ(double_to_bits(bits_to_double(double_to_bits(-0.0))),
    double_to_bits(-0.0)); 
}

TEST(BitsToDouble, RoundTripInf) { 
    EXPECT_EQ(double_to_bits(bits_to_double(double_to_bits(D_POS_INF))), 
    double_to_bits(D_POS_INF)); 
}

TEST(BitsToDouble, RoundTripNaN) { 
    EXPECT_EQ(double_to_bits(bits_to_double(double_to_bits(D_NAN))),
    double_to_bits(D_NAN)); 
}

// 2)
// (a) is_finite
TEST(FloatIsFinite, Normal) { EXPECT_TRUE(float_is_finite(F_NORMAL)); }
TEST(FloatIsFinite, NegZero) { EXPECT_TRUE(float_is_finite(F_NEG_ZERO)); }
TEST(FloatIsFinite, Subnormal) { EXPECT_TRUE(float_is_finite(F_SUBNORMAL)); }
TEST(FloatIsFinite, PosInfinity) { EXPECT_FALSE(float_is_finite(F_POS_INF)); }
TEST(FloatIsFinite, NegInfinity) { EXPECT_FALSE(float_is_finite(F_NEG_INF)); }
TEST(FloatIsFinite, NaN) { EXPECT_FALSE(float_is_finite(F_NAN)); }

TEST(DoubleIsFinite, Normal) { EXPECT_TRUE(double_is_finite(D_NORMAL)); }
TEST(DoubleIsFinite, NegZero) { EXPECT_TRUE(double_is_finite(D_NEG_ZERO)); }
TEST(DoubleIsFinite, Subnormal) { EXPECT_TRUE(double_is_finite(D_SUBNORMAL)); }
TEST(DoubleIsFinite, PosInfinity) { EXPECT_FALSE(double_is_finite(D_POS_INF)); }
TEST(DoubleIsFinite, NegInfinity) { EXPECT_FALSE(double_is_finite(D_NEG_INF)); }
TEST(DoubleIsFinite, NaN) { EXPECT_FALSE(double_is_finite(D_NAN)); }

// (b) is_inf
TEST(FloatIsInf, PosInfinity) { EXPECT_TRUE(float_is_inf(F_POS_INF)); }
TEST(FloatIsInf, NegInfinity) { EXPECT_TRUE(float_is_inf(F_NEG_INF)); }
TEST(FloatIsInf, Normal) { EXPECT_FALSE(float_is_inf(F_NORMAL)); }
TEST(FloatIsInf, NaN) { EXPECT_FALSE(float_is_inf(F_NAN)); }
TEST(FloatIsInf, Zero) { EXPECT_FALSE(float_is_inf(F_POS_ZERO)); }

TEST(DoubleIsInf, PosInfinity) { EXPECT_TRUE(double_is_inf(D_POS_INF)); }
TEST(DoubleIsInf, NegInfinity) { EXPECT_TRUE(double_is_inf(D_NEG_INF)); }
TEST(DoubleIsInf, Normal) { EXPECT_FALSE(double_is_inf(D_NORMAL)); }
TEST(DoubleIsInf, NaN) { EXPECT_FALSE(double_is_inf(D_NAN)); }
TEST(DoubleIsInf, Zero) { EXPECT_FALSE(double_is_inf(D_POS_ZERO)); }

// (c) is_positive_inf
TEST(FloatIsPosInf, PosInfinity) { EXPECT_TRUE(float_is_positive_inf(F_POS_INF)); }
TEST(FloatIsPosInf, NegInfinity) { EXPECT_FALSE(float_is_positive_inf(F_NEG_INF)); }
TEST(FloatIsPosInf, Normal) { EXPECT_FALSE(float_is_positive_inf(F_NORMAL)); }

TEST(DoubleIsPosInf, PosInfinity) { EXPECT_TRUE(double_is_positive_inf(D_POS_INF)); }
TEST(DoubleIsPosInf, NegInfinity) { EXPECT_FALSE(double_is_positive_inf(D_NEG_INF)); }
TEST(DoubleIsPosInf, Normal) { EXPECT_FALSE(double_is_positive_inf(D_NORMAL)); }

// (d) is_negative_inf
TEST(FloatIsNegInf, NegInfinity) { EXPECT_TRUE(float_is_negative_inf(F_NEG_INF)); }
TEST(FloatIsNegInf, PosInfinity) { EXPECT_FALSE(float_is_negative_inf(F_POS_INF)); }
TEST(FloatIsNegInf, Normal) { EXPECT_FALSE(float_is_negative_inf(F_NORMAL)); }

TEST(DoubleIsNegInf, NegInfinity) { EXPECT_TRUE(double_is_negative_inf(D_NEG_INF)); }
TEST(DoubleIsNegInf, PosInfinity) { EXPECT_FALSE(double_is_negative_inf(D_POS_INF)); }
TEST(DoubleIsNegInf, Normal) { EXPECT_FALSE(double_is_negative_inf(D_NORMAL)); }

// (e) is_zero
TEST(FloatIsZero, PosZero) { EXPECT_TRUE(float_is_zero(F_POS_ZERO)); }
TEST(FloatIsZero, NegZero) { EXPECT_TRUE(float_is_zero(F_NEG_ZERO)); }
TEST(FloatIsZero, Normal) { EXPECT_FALSE(float_is_zero(F_NORMAL)); }
TEST(FloatIsZero, Subnormal) { EXPECT_FALSE(float_is_zero(F_SUBNORMAL)); }

TEST(DoubleIsZero, PosZero) { EXPECT_TRUE(double_is_zero(D_POS_ZERO)); }
TEST(DoubleIsZero, NegZero) { EXPECT_TRUE(double_is_zero(D_NEG_ZERO)); }
TEST(DoubleIsZero, Normal) { EXPECT_FALSE(double_is_zero(D_NORMAL)); }
TEST(DoubleIsZero, Subnormal) { EXPECT_FALSE(double_is_zero(D_SUBNORMAL)); }

// (f) is_positive_zero
TEST(FloatIsPosZero, PosZero) { EXPECT_TRUE(float_is_positive_zero(F_POS_ZERO)); }
TEST(FloatIsPosZero, NegZero) { EXPECT_FALSE(float_is_positive_zero(F_NEG_ZERO)); }
TEST(FloatIsPosZero, Normal) { EXPECT_FALSE(float_is_positive_zero(F_NORMAL)); }

TEST(DoubleIsPosZero, PosZero) { EXPECT_TRUE(double_is_positive_zero(D_POS_ZERO)); }
TEST(DoubleIsPosZero, NegZero) { EXPECT_FALSE(double_is_positive_zero(D_NEG_ZERO)); }
TEST(DoubleIsPosZero, Normal) { EXPECT_FALSE(double_is_positive_zero(D_NORMAL)); }

// (g) is_negative_zero
TEST(FloatIsNegZero, NegZero) { EXPECT_TRUE(float_is_negative_zero(F_NEG_ZERO)); }
TEST(FloatIsNegZero, PosZero) { EXPECT_FALSE(float_is_negative_zero(F_POS_ZERO)); }
TEST(FloatIsNegZero, Normal) { EXPECT_FALSE(float_is_negative_zero(F_NORMAL)); }

TEST(DoubleIsNegZero, NegZero) { EXPECT_TRUE(double_is_negative_zero(D_NEG_ZERO)); }
TEST(DoubleIsNegZero, PosZero) { EXPECT_FALSE(double_is_negative_zero(D_POS_ZERO)); }
TEST(DoubleIsNegZero, Normal) { EXPECT_FALSE(double_is_negative_zero(D_NORMAL)); }

// (h) is_nan
TEST(FloatIsNaN, NaN) { EXPECT_TRUE(float_is_nan(F_NAN)); }
TEST(FloatIsNaN, Normal) { EXPECT_FALSE(float_is_nan(F_NORMAL)); }
TEST(FloatIsNaN, PosInfinity) { EXPECT_FALSE(float_is_nan(F_POS_INF)); }
TEST(FloatIsNaN, Zero) { EXPECT_FALSE(float_is_nan(F_POS_ZERO)); }

TEST(DoubleIsNaN, NaN) { EXPECT_TRUE(double_is_nan(D_NAN)); }
TEST(DoubleIsNaN, Normal) { EXPECT_FALSE(double_is_nan(D_NORMAL)); }
TEST(DoubleIsNaN, PosInfinity) { EXPECT_FALSE(double_is_nan(D_POS_INF)); }
TEST(DoubleIsNaN, Zero) { EXPECT_FALSE(double_is_nan(D_POS_ZERO)); }

// (i) is_normal
TEST(FloatIsNormal, Normal) { EXPECT_TRUE(float_is_normal(F_NORMAL)); }
TEST(FloatIsNormal, Negative) { EXPECT_TRUE(float_is_normal(F_NEG)); }
TEST(FloatIsNormal, Zero) { EXPECT_FALSE(float_is_normal(F_POS_ZERO)); }
TEST(FloatIsNormal, Subnormal) { EXPECT_FALSE(float_is_normal(F_SUBNORMAL)); }
TEST(FloatIsNormal, Infinity) { EXPECT_FALSE(float_is_normal(F_POS_INF)); }
TEST(FloatIsNormal, NaN) { EXPECT_FALSE(float_is_normal(F_NAN)); }

TEST(DoubleIsNormal, Normal) { EXPECT_TRUE(double_is_normal(D_NORMAL)); }
TEST(DoubleIsNormal, Negative) { EXPECT_TRUE(double_is_normal(D_NEG)); }
TEST(DoubleIsNormal, Zero) { EXPECT_FALSE(double_is_normal(D_POS_ZERO)); }
TEST(DoubleIsNormal, Subnormal) { EXPECT_FALSE(double_is_normal(D_SUBNORMAL)); }
TEST(DoubleIsNormal, Infinity) { EXPECT_FALSE(double_is_normal(D_POS_INF)); }
TEST(DoubleIsNormal, NaN) { EXPECT_FALSE(double_is_normal(D_NAN)); }

// (j) is_subnormal
TEST(FloatIsSubnormal, Subnormal) { EXPECT_TRUE(float_is_subnormal(F_SUBNORMAL)); }
TEST(FloatIsSubnormal, Normal) { EXPECT_FALSE(float_is_subnormal(F_NORMAL)); }
TEST(FloatIsSubnormal, Zero) { EXPECT_FALSE(float_is_subnormal(F_POS_ZERO)); }
TEST(FloatIsSubnormal, Infinity) { EXPECT_FALSE(float_is_subnormal(F_POS_INF)); }

TEST(DoubleIsSubnormal, Subnormal) { EXPECT_TRUE(double_is_subnormal(D_SUBNORMAL)); }
TEST(DoubleIsSubnormal, Normal) { EXPECT_FALSE(double_is_subnormal(D_NORMAL)); }
TEST(DoubleIsSubnormal, Zero) { EXPECT_FALSE(double_is_subnormal(D_POS_ZERO)); }
TEST(DoubleIsSubnormal, Infinity) { EXPECT_FALSE(double_is_subnormal(D_POS_INF)); }

// (k) is_signed
TEST(FloatIsSigned, Negative) { EXPECT_TRUE(float_is_signed(F_NEG)); }
TEST(FloatIsSigned, NegZero) { EXPECT_TRUE(float_is_signed(F_NEG_ZERO)); }
TEST(FloatIsSigned, NegInfinity) { EXPECT_TRUE(float_is_signed(F_NEG_INF)); }
TEST(FloatIsSigned, Positive) { EXPECT_FALSE(float_is_signed(F_NORMAL)); }
TEST(FloatIsSigned, PosZero) { EXPECT_FALSE(float_is_signed(F_POS_ZERO)); }
TEST(FloatIsSigned, PosInfinity) { EXPECT_FALSE(float_is_signed(F_POS_INF)); }

TEST(DoubleIsSigned, Negative) { EXPECT_TRUE(double_is_signed(D_NEG)); }
TEST(DoubleIsSigned, NegZero) { EXPECT_TRUE(double_is_signed(D_NEG_ZERO)); }
TEST(DoubleIsSigned, NegInfinity) { EXPECT_TRUE(double_is_signed(D_NEG_INF)); }
TEST(DoubleIsSigned, Positive) { EXPECT_FALSE(double_is_signed(D_NORMAL)); }
TEST(DoubleIsSigned, PosZero) { EXPECT_FALSE(double_is_signed(D_POS_ZERO)); }
TEST(DoubleIsSigned, PosInfinity) { EXPECT_FALSE(double_is_signed(D_POS_INF)); }

// (l) classify
TEST(FloatClassify, Normal) { EXPECT_EQ(float_classify(F_NORMAL), FP_CLASS_NORMAL); }
TEST(FloatClassify, Subnormal) { EXPECT_EQ(float_classify(F_SUBNORMAL), FP_CLASS_SUBNORMAL); }
TEST(FloatClassify, Zero) { EXPECT_EQ(float_classify(F_POS_ZERO), FP_CLASS_ZERO); }
TEST(FloatClassify, NegZero) { EXPECT_EQ(float_classify(F_NEG_ZERO), FP_CLASS_ZERO); }
TEST(FloatClassify, Infinity) { EXPECT_EQ(float_classify(F_POS_INF), FP_CLASS_INFINITE); }
TEST(FloatClassify, NaN) { EXPECT_EQ(float_classify(F_NAN), FP_CLASS_NAN); }

TEST(DoubleClassify, Normal) { EXPECT_EQ(double_classify(D_NORMAL), FP_CLASS_NORMAL); }
TEST(DoubleClassify, Subnormal) { EXPECT_EQ(double_classify(D_SUBNORMAL), FP_CLASS_SUBNORMAL); }
TEST(DoubleClassify, Zero) { EXPECT_EQ(double_classify(D_POS_ZERO), FP_CLASS_ZERO); }
TEST(DoubleClassify, NegZero) { EXPECT_EQ(double_classify(D_NEG_ZERO), FP_CLASS_ZERO); }
TEST(DoubleClassify, Infinity) { EXPECT_EQ(double_classify(D_POS_INF), FP_CLASS_INFINITE); }
TEST(DoubleClassify, NaN) { EXPECT_EQ(double_classify(D_NAN), FP_CLASS_NAN); }


// 3)
// (a) abs
TEST(FloatAbs, Positive) { EXPECT_EQ(float_to_bits(float_abs(1.0f)), float_to_bits(1.0f)); }
TEST(FloatAbs, Negative) { EXPECT_EQ(float_to_bits(float_abs(-1.0f)), float_to_bits(1.0f)); }
TEST(FloatAbs, NegZero) { EXPECT_EQ(float_to_bits(float_abs(-0.0f)), float_to_bits(0.0f)); }
TEST(FloatAbs, NegInfinity) { EXPECT_EQ(float_to_bits(float_abs(F_NEG_INF)), float_to_bits(F_POS_INF)); }
TEST(FloatAbs, NaN) { EXPECT_TRUE(float_is_nan(float_abs(F_NAN))); }

TEST(DoubleAbs, Positive) { EXPECT_EQ(double_to_bits(double_abs(1.0)), double_to_bits(1.0)); }
TEST(DoubleAbs, Negative) { EXPECT_EQ(double_to_bits(double_abs(-1.0)), double_to_bits(1.0)); }
TEST(DoubleAbs, NegZero) { EXPECT_EQ(double_to_bits(double_abs(-0.0)), double_to_bits(0.0)); }
TEST(DoubleAbs, NegInfinity) { EXPECT_EQ(double_to_bits(double_abs(D_NEG_INF)), double_to_bits(D_POS_INF)); }
TEST(DoubleAbs, NaN) { EXPECT_TRUE(double_is_nan(double_abs(D_NAN))); }

// (b) min  
TEST(FloatMin, Basic) { EXPECT_EQ(float_min(1.0f, 2.0f), 1.0f); }
TEST(FloatMin, NegativeWins) { EXPECT_EQ(float_min(-3.0f, 2.0f), -3.0f); }
TEST(FloatMin, NaNLeft) { EXPECT_EQ(float_to_bits(float_min(F_NAN, 1.0f)), float_to_bits(1.0f)); }
TEST(FloatMin, NaNRight) { EXPECT_EQ(float_to_bits(float_min(1.0f, F_NAN)), float_to_bits(1.0f)); }
TEST(FloatMin, SignedZero) { EXPECT_EQ(float_to_bits(float_min(-0.0f, 0.0f)), float_to_bits(-0.0f)); }

TEST(DoubleMin, Basic) { EXPECT_EQ(double_min(1.0, 2.0), 1.0); }
TEST(DoubleMin, NaNLeft) { EXPECT_EQ(double_to_bits(double_min(D_NAN, 1.0)), double_to_bits(1.0)); }
TEST(DoubleMin, NaNRight) { EXPECT_EQ(double_to_bits(double_min(1.0, D_NAN)), double_to_bits(1.0)); }
TEST(DoubleMin, SignedZero) { EXPECT_EQ(double_to_bits(double_min(-0.0, 0.0)), double_to_bits(-0.0)); }

// (c) max  
TEST(FloatMax, Basic) { EXPECT_EQ(float_max(1.0f, 2.0f), 2.0f); }
TEST(FloatMax, NegativeArgs) { EXPECT_EQ(float_max(-3.0f, -1.0f), -1.0f); }
TEST(FloatMax, NaNLeft) { EXPECT_EQ(float_to_bits(float_max(F_NAN, 1.0f)), float_to_bits(1.0f)); }
TEST(FloatMax, NaNRight) { EXPECT_EQ(float_to_bits(float_max(1.0f, F_NAN)), float_to_bits(1.0f)); }
TEST(FloatMax, SignedZero) { EXPECT_EQ(float_to_bits(float_max(-0.0f, 0.0f)), float_to_bits(0.0f)); }

TEST(DoubleMax, Basic) { EXPECT_EQ(double_max(1.0, 2.0), 2.0); }
TEST(DoubleMax, NaNLeft) { EXPECT_EQ(double_to_bits(double_max(D_NAN, 1.0)), double_to_bits(1.0)); }
TEST(DoubleMax, NaNRight) { EXPECT_EQ(double_to_bits(double_max(1.0, D_NAN)), double_to_bits(1.0)); }
TEST(DoubleMax, SignedZero) { EXPECT_EQ(double_to_bits(double_max(-0.0, 0.0)), double_to_bits(0.0)); }

// (d) clamp 
TEST(FloatClamp, InsideRange) { EXPECT_EQ(float_clamp(0.5f, 0.0f, 1.0f), 0.5f); }
TEST(FloatClamp, BelowLo) { EXPECT_EQ(float_clamp(-1.0f, 0.0f, 1.0f), 0.0f); }
TEST(FloatClamp, AboveHi) { EXPECT_EQ(float_clamp(2.0f, 0.0f, 1.0f), 1.0f); }
TEST(FloatClamp, AtLo) { EXPECT_EQ(float_clamp(0.0f, 0.0f, 1.0f), 0.0f); }
TEST(FloatClamp, AtHi) { EXPECT_EQ(float_clamp(1.0f, 0.0f, 1.0f), 1.0f); }

TEST(DoubleClamp, InsideRange){ EXPECT_EQ(double_clamp(0.5, 0.0, 1.0), 0.5); }
TEST(DoubleClamp, BelowLo) { EXPECT_EQ(double_clamp(-1.0, 0.0, 1.0), 0.0); }
TEST(DoubleClamp, AboveHi) { EXPECT_EQ(double_clamp(2.0, 0.0, 1.0), 1.0); }

// 4
// (a) equal_eps 
TEST(FloatEqualEps, ExactMatch) { EXPECT_TRUE(float_equal_eps(1.0f, 1.0f, 0.0f)); }
TEST(FloatEqualEps, WithinEps) { EXPECT_TRUE(float_equal_eps(1.0f, 1.0f + 1e-6f, 1e-5f)); }
TEST(FloatEqualEps, OutsideEps) { EXPECT_FALSE(float_equal_eps(1.0f, 2.0f, 0.5f)); }
TEST(FloatEqualEps, NaN) { EXPECT_FALSE(float_equal_eps(F_NAN, F_NAN, 1.0f)); }

TEST(DoubleEqualEps, ExactMatch) { EXPECT_TRUE(double_equal_eps(1.0, 1.0, 0.0)); }
TEST(DoubleEqualEps, WithinEps) { EXPECT_TRUE(double_equal_eps(1.0, 1.0 + 1e-10, 1e-9)); }
TEST(DoubleEqualEps, OutsideEps) { EXPECT_FALSE(double_equal_eps(1.0, 2.0, 0.5)); }
TEST(DoubleEqualEps, NaN) { EXPECT_FALSE(double_equal_eps(D_NAN, D_NAN, 1.0)); }

// (b) equal (ULP-based) 
TEST(FloatEqual, Same) { EXPECT_TRUE(float_equal(1.0f, 1.0f)); }
TEST(FloatEqual, AdjacentULP) {
    // 1 ULP away from 1.0f must still be considered equal.
    uint32_t bits = float_to_bits(1.0f) + 1u;
    EXPECT_TRUE(float_equal(1.0f, bits_to_float(bits)));
}
TEST(FloatEqual, FarApart) { EXPECT_FALSE(float_equal(1.0f, 2.0f)); }
TEST(FloatEqual, NaN) { EXPECT_FALSE(float_equal(F_NAN, F_NAN)); }
TEST(FloatEqual, PosNegZero) { EXPECT_TRUE(float_equal(0.0f, -0.0f)); }
TEST(FloatEqual, BothInf) { EXPECT_TRUE(float_equal(F_POS_INF, F_POS_INF)); }
TEST(FloatEqual, OppositeInf) { EXPECT_FALSE(float_equal(F_POS_INF, F_NEG_INF)); }

TEST(DoubleEqual, Same) { EXPECT_TRUE(double_equal(1.0, 1.0)); }
TEST(DoubleEqual, AdjacentULP){
    uint64_t bits = double_to_bits(1.0) + 1ull;
    EXPECT_TRUE(double_equal(1.0, bits_to_double(bits)));
}
TEST(DoubleEqual, FarApart) { EXPECT_FALSE(double_equal(1.0, 2.0)); }
TEST(DoubleEqual, NaN) { EXPECT_FALSE(double_equal(D_NAN, D_NAN)); }
TEST(DoubleEqual, PosNegZero) { EXPECT_TRUE(double_equal(0.0, -0.0)); }

// (c) less_eps 
TEST(FloatLessEps, Clearly) { EXPECT_TRUE(float_less_eps(1.0f, 2.0f, 0.5f)); }
TEST(FloatLessEps, WithinEps) { EXPECT_FALSE(float_less_eps(1.0f, 1.0f + 1e-6f, 1e-5f)); }
TEST(FloatLessEps, Equal) { EXPECT_FALSE(float_less_eps(1.0f, 1.0f, 0.0f)); }
TEST(FloatLessEps, Greater) { EXPECT_FALSE(float_less_eps(2.0f, 1.0f, 0.5f)); }
TEST(FloatLessEps, NaN) { EXPECT_FALSE(float_less_eps(F_NAN, 1.0f, 0.0f)); }

TEST(DoubleLessEps, Clearly) { EXPECT_TRUE(double_less_eps(1.0, 2.0, 0.5)); }
TEST(DoubleLessEps, WithinEps) { EXPECT_FALSE(double_less_eps(1.0, 1.0 + 1e-10, 1e-9)); }
TEST(DoubleLessEps, NaN) { EXPECT_FALSE(double_less_eps(D_NAN, 1.0, 0.0)); }

// (d) less (arbitrary) 
TEST(FloatLess, Clearly) { EXPECT_TRUE(float_less(1.0f, 2.0f)); }
TEST(FloatLess, Equal) { EXPECT_FALSE(float_less(1.0f, 1.0f)); }
TEST(FloatLess, Greater) { EXPECT_FALSE(float_less(2.0f, 1.0f)); }
TEST(FloatLess, NaN) { EXPECT_FALSE(float_less(F_NAN, 1.0f)); }
TEST(FloatLess, NegInfSmallest) { EXPECT_TRUE(float_less(F_NEG_INF, -1e38f)); }

TEST(DoubleLess, Clearly) { EXPECT_TRUE(double_less(1.0, 2.0)); }
TEST(DoubleLess, NaN) { EXPECT_FALSE(double_less(D_NAN, 1.0)); }

// (e) greater_eps 
TEST(FloatGreaterEps, Clearly) { EXPECT_TRUE(float_greater_eps(2.0f, 1.0f, 0.5f)); }
TEST(FloatGreaterEps, WithinEps) { EXPECT_FALSE(float_greater_eps(1.0f + 1e-6f, 1.0f, 1e-5f)); }
TEST(FloatGreaterEps, Equal) { EXPECT_FALSE(float_greater_eps(1.0f, 1.0f, 0.0f)); }
TEST(FloatGreaterEps, NaN) { EXPECT_FALSE(float_greater_eps(F_NAN, 1.0f, 0.0f)); }

TEST(DoubleGreaterEps, Clearly) { EXPECT_TRUE(double_greater_eps(2.0, 1.0, 0.5)); }
TEST(DoubleGreaterEps, WithinEps){ EXPECT_FALSE(double_greater_eps(1.0 + 1e-10, 1.0, 1e-9)); }
TEST(DoubleGreaterEps, NaN) { EXPECT_FALSE(double_greater_eps(D_NAN, 1.0, 0.0)); }

// (f) greater (arbitrary) 
TEST(FloatGreater, Clearly) { EXPECT_TRUE(float_greater(2.0f, 1.0f)); }
TEST(FloatGreater, Equal) { EXPECT_FALSE(float_greater(1.0f, 1.0f)); }
TEST(FloatGreater, Less) { EXPECT_FALSE(float_greater(1.0f, 2.0f)); }
TEST(FloatGreater, NaN) { EXPECT_FALSE(float_greater(F_NAN, 1.0f)); }
TEST(FloatGreater, PosInfLargest) { EXPECT_TRUE(float_greater(F_POS_INF, 1e38f)); }

TEST(DoubleGreater, Clearly) { EXPECT_TRUE(double_greater(2.0, 1.0)); }
TEST(DoubleGreater, NaN) { EXPECT_FALSE(double_greater(D_NAN, 1.0)); }
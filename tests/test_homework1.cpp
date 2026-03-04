#include "../Homework1.h"

#include <gtest/gtest.h>
#include <cmath> 
#include <cstdint>

// IEEE 754 float layout  (32 bits): [s|eeeeeeee|mmmmmmmmmmmmmmmmmmmmmmm]
// IEEE 754 double layout (64 bits): [s|eeeeeeeeeee|mmmm...mmmm] (52 m-bits)
// Digit separator ' groups the three fields so the structure is visible directly.

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
    // Exponent all-ones, mantissa zero.
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
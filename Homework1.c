#include "Homework1.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static_assert(sizeof(float) == sizeof(uint32_t));
static_assert(sizeof(double) == sizeof(uint64_t));

[[nodiscard]] uint32_t float_to_bits(float value)
{
    if (sizeof(float) != sizeof(uint32_t)) {
        perror("float and uint32_t sizes do not match\n");
        exit(1);
    }
    uint32_t bits = {0};
    memcpy(&bits, &value, sizeof bits);
    return bits;
}

[[nodiscard]] uint64_t double_to_bits(double value)
{
    if (sizeof(double) != sizeof(uint64_t)) {
        perror("double and uint64_t sizes do not match\n");
        exit(1);
    }
    uint64_t bits = {0};
    memcpy(&bits, &value, sizeof bits);
    return bits;
}
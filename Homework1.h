#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// (1)
uint32_t float_to_bits(float value);
uint64_t double_to_bits(double value);

#ifdef __cplusplus
}
#endif
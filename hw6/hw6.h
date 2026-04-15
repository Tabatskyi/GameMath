#pragma once

#include "../hw3/hw3.h"

typedef struct {
    double w;
    double x;
    double y;
    double z;
} Quaternion;

Quaternion normalize_quaternion(Quaternion q);
Quaternion conjugate(Quaternion q);
Quaternion multiply_quaternion(Quaternion a, Quaternion b);
Vector3 rotate_vector_by_quaternion(Vector3 v, Quaternion q);

void print_quaternion(const char* label, Quaternion q);
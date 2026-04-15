#include "hw6.h"

#include <math.h>
#include <stdio.h>

Quaternion normalize_quaternion(Quaternion q) {
    double norm = sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
    if (double_is_zero(norm)) {
        return (Quaternion){1.0, 0.0, 0.0, 0.0};
    }

    return (Quaternion){q.w / norm, q.x / norm, q.y / norm, q.z / norm};
}

Quaternion conjugate(Quaternion q) {
    return (Quaternion){q.w, -q.x, -q.y, -q.z};
}

Quaternion multiply_quaternion(Quaternion a, Quaternion b) {
    return (Quaternion){
        a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,
        a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
        a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
        a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w
    };
}

Vector3 rotate_vector_by_quaternion(Vector3 v, Quaternion q) {
    Quaternion unit_q = normalize_quaternion(q);
    Quaternion pure_v = {0.0, v.x, v.y, v.z};

    Quaternion rotated_q = multiply_quaternion(
        multiply_quaternion(unit_q, pure_v),
        conjugate(unit_q)
    );

    return (Vector3){rotated_q.x, rotated_q.y, rotated_q.z};
}

void print_quaternion(const char* label, Quaternion q) {
    printf("%s (%.15f, %.15f, %.15f, %.15f)\n", label, q.w, q.x, q.y, q.z);
}

int main(void) {
    // 1) Rotate vector (1.0, 1.0, 1.0) with quaternion (+0.808, +0.492, -0.015, +0.325).
    // 2) Rotate vector (1.0, 1.0, 1.0) with quaternion (+0.271, +0.271, +0.653, +0.653).
    const Vector3 input_vector = {1.0, 1.0, 1.0};

    const Quaternion q1 = {+0.808, +0.492, -0.015, +0.325};
    const Quaternion q2 = {+0.271, +0.271, +0.653, +0.653};

    const Vector3 rotated_1 = rotate_vector_by_quaternion(input_vector, q1);
    const Vector3 rotated_2 = rotate_vector_by_quaternion(input_vector, q2);

    print_vector3("Input vector:", input_vector);
    print_quaternion("q1:", q1);
    print_vector3("1) Rotated with q1:", rotated_1);
    print_quaternion("q2:", q2);
    print_vector3("2) Rotated with q2:", rotated_2);

    return 0;
}
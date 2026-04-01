#include "hw.h"

Vector3 add3(Vector3 a, Vector3 b) {
    return (Vector3){a.x + b.x, a.y + b.y, a.z + b.z};
}

double dot3(Vector3 a, Vector3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 scale3(Vector3 v, double scalar) {
    return (Vector3){v.x * scalar, v.y * scalar, v.z * scalar};
}

void print_vector3(const char* label, Vector3 v) {
    printf("%s (%.15f, %.15f, %.15f)\n", label, v.x, v.y, v.z);
}

int main(void) {
    // a) 𝑎̅(+5.6, – 1.2, – 4.5) + 𝑏̅(+1.1, +2.2, +5.1)
    Vector3 a_a = {+5.6, -1.2, -4.5};
    Vector3 b_a = {+1.1, +2.2, +5.1};
    Vector3 result_a = add3(a_a, b_a);
    print_vector3("Result a:", result_a);

    // b) 𝑎̅(+4.3, +0.2, – 1.5) + 𝑏̅(– 1.1, +3.0, +1.2)
    Vector3 a_b = {+4.3, +0.2, -1.5};
    Vector3 b_b = {-1.1, +3.0, +1.2};
    Vector3 result_b = add3(a_b, b_b);
    print_vector3("Result b:", result_b);

    // c) 𝑎̅(+5.4, −1.1, +2.9) + 𝑏̅(−3.6, +0.5, −1.8)
    Vector3 a_c = {+5.4, -1.1, +2.9};
    Vector3 b_c = {-3.6, +0.5, -1.8};
    Vector3 result_c = add3(a_c, b_c);
    print_vector3("Result c:", result_c);

    // d) 𝑎̅(+2.7, −0.9, +3.8) + 𝑏̅(−1.4, +2.5, −1.2)
    Vector3 a_d = {+2.7, -0.9, +3.8};
    Vector3 b_d = {-1.4, +2.5, -1.2};
    Vector3 result_d = add3(a_d, b_d);
    print_vector3("Result d:", result_d);

    // e) 𝑎̅(−2.1, +3.7, +0.5) ∙ −1.1
    Vector3 a_e = {-2.1, +3.7, +0.5};
    double scalar_e = -1.1;
    Vector3 result_e = scale3(a_e, scalar_e);
    print_vector3("Result e:", result_e);

    // f) 𝑎̅(+6.6, −1.2, +3.2) ∙ +2.6
    Vector3 a_f = {+6.6, -1.2, +3.2};
    double scalar_f = +2.6;
    Vector3 result_f = scale3(a_f, scalar_f);
    print_vector3("Result f:", result_f);

    // g) 𝑎̅(+2.5, −1.8, +3.4) + 𝑏̅(−1.2, +2.9, −0.6) ∙ +0.7
    Vector3 a_g = {+2.5, -1.8, +3.4};
    Vector3 b_g = {-1.2, +2.9, -0.6};
    double scalar_g = +0.7;
    Vector3 b_g_scaled = scale3(b_g, scalar_g);
    Vector3 result_g = add3(a_g, b_g_scaled);
    print_vector3("Result g:", result_g);

    // h) 𝑎̅(−3.1, +4.2, −2.7) + 𝑏̅(+1.8, −2.4, +0.9) ∙ −1.5
    Vector3 a_h = {-3.1, +4.2, -2.7};
    Vector3 b_h = {+1.8, -2.4, +0.9};
    double scalar_h = -1.5;
    Vector3 b_h_scaled = scale3(b_h, scalar_h);
    Vector3 result_h = add3(a_h, b_h_scaled);
    print_vector3("Result h:", result_h);

    // i) 𝑎̅(+3.1, −2.4, +1.7) ∙ 𝑏̅(−0.8, +1.4, −2.3)
    Vector3 a_i = {+3.1, -2.4, +1.7};
    Vector3 b_i = {-0.8, +1.4, -2.3};
    double result_i = dot3(a_i, b_i);
    printf("Result i: %.15f\n", result_i);

    return 0;
}
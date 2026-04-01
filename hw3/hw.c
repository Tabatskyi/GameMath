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

double mag2(Vector2 v) {
    return sqrt((v.x * v.x) + (v.y * v.y));
}

double dot2(Vector2 a, Vector2 b) {
    return a.x * b.x + a.y * b.y;
}

void print_vector3(const char* label, Vector3 v) {
    printf("%s (%.15f, %.15f, %.15f)\n", label, v.x, v.y, v.z);
}

void print_vector2(const char* label, Vector2 v) {
    printf("%s (%.15f, %.15f)\n", label, v.x, v.y);
}

double to_radians(double degrees) {
    return degrees * (M_PI / 180.0);
}

double to_degrees(double radians) {
    return radians * (180.0 / M_PI);
}

double angle(Vector2 a, Vector2 b) {
    double mag_v1 = mag2(a);
    double mag_v2 = mag2(b);

    if (double_is_zero(mag_v1) || double_is_zero(mag_v2)) {
        return 0.0;
    }

    double dot = dot2(a, b);
    double cos_theta = dot / (mag_v1 * mag_v2);

    cos_theta = double_clamp(cos_theta, -1.0, 1.0);
    
    return acos(cos_theta) * (180.0 / M_PI);
}

void check_visibility(char* label, Vector2 a, Vector2 b) {
    Vector2 direction_to_enemy = {1.0, 0.0};
    Vector2 direction_to_player = {-1.0, 0.0};
    
    double max_angle = 20.0; 
    
    double angle_player = angle(a, direction_to_enemy);
    double angle_enemy = angle(b, direction_to_player);

    bool player_sees_enemy = !double_greater(angle_player, max_angle);
    bool enemy_sees_player = !double_greater(angle_enemy, max_angle);
    
    printf("%s):\n", label);
    printf("Player -> Enemy: %.15f deg -> %s\n", angle_player, player_sees_enemy ? "YES" : "NO");
    printf("Enemy -> Player: %.15f deg -> %s\n", angle_enemy, enemy_sees_player ? "YES" : "NO");
}

int main(void) {
    printf("(1)\n");
    // a) 𝑎̅(+5.6, – 1.2, – 4.5) + 𝑏̅(+1.1, +2.2, +5.1)
    Vector3 a_a = {+5.6, -1.2, -4.5};
    Vector3 b_a = {+1.1, +2.2, +5.1};
    Vector3 result_a = add3(a_a, b_a);
    print_vector3("a):", result_a);

    // b) 𝑎̅(+4.3, +0.2, – 1.5) + 𝑏̅(– 1.1, +3.0, +1.2)
    Vector3 a_b = {+4.3, +0.2, -1.5};
    Vector3 b_b = {-1.1, +3.0, +1.2};
    Vector3 result_b = add3(a_b, b_b);
    print_vector3("b):", result_b);

    // c) 𝑎̅(+5.4, −1.1, +2.9) + 𝑏̅(−3.6, +0.5, −1.8)
    Vector3 a_c = {+5.4, -1.1, +2.9};
    Vector3 b_c = {-3.6, +0.5, -1.8};
    Vector3 result_c = add3(a_c, b_c);
    print_vector3("c):", result_c);

    // d) 𝑎̅(+2.7, −0.9, +3.8) + 𝑏̅(−1.4, +2.5, −1.2)
    Vector3 a_d = {+2.7, -0.9, +3.8};
    Vector3 b_d = {-1.4, +2.5, -1.2};
    Vector3 result_d = add3(a_d, b_d);
    print_vector3("d):", result_d);

    // e) 𝑎̅(−2.1, +3.7, +0.5) ∙ −1.1
    Vector3 a_e = {-2.1, +3.7, +0.5};
    double scalar_e = -1.1;
    Vector3 result_e = scale3(a_e, scalar_e);
    print_vector3("e):", result_e);

    // f) 𝑎̅(+6.6, −1.2, +3.2) ∙ +2.6
    Vector3 a_f = {+6.6, -1.2, +3.2};
    double scalar_f = +2.6;
    Vector3 result_f = scale3(a_f, scalar_f);
    print_vector3("f):", result_f);

    // g) 𝑎̅(+2.5, −1.8, +3.4) + 𝑏̅(−1.2, +2.9, −0.6) ∙ +0.7
    Vector3 a_g = {+2.5, -1.8, +3.4};
    Vector3 b_g = {-1.2, +2.9, -0.6};
    double scalar_g = +0.7;
    Vector3 b_g_scaled = scale3(b_g, scalar_g);
    Vector3 result_g = add3(a_g, b_g_scaled);
    print_vector3("g):", result_g);

    // h) 𝑎̅(−3.1, +4.2, −2.7) + 𝑏̅(+1.8, −2.4, +0.9) ∙ −1.5
    Vector3 a_h = {-3.1, +4.2, -2.7};
    Vector3 b_h = {+1.8, -2.4, +0.9};
    double scalar_h = -1.5;
    Vector3 b_h_scaled = scale3(b_h, scalar_h);
    Vector3 result_h = add3(a_h, b_h_scaled);
    print_vector3("h):", result_h);

    // i) 𝑎̅(+3.1, −2.4, +1.7) ∙ 𝑏̅(−0.8, +1.4, −2.3)
    Vector3 a_i = {+3.1, -2.4, +1.7};
    Vector3 b_i = {-0.8, +1.4, -2.3};
    double result_i = dot3(a_i, b_i);
    printf("i): %.15f\n", result_i);

    printf("\n(2)\n");
    // a) 𝑎̅(+1.0, +0.0) and 𝑏̅(−1.0, +0.0)
    check_visibility("a", (Vector2){+1.0, +0.0}, (Vector2){-1.0, +0.0});
    // b) 𝑎̅(+0.0, +1.0) and 𝑏̅(+1.0, +0.0)
    check_visibility("b", (Vector2){+0.0, +1.0}, (Vector2){+1.0, +0.0});
    // c) 𝑎̅(+1.0, +0.0) and 𝑏̅(−0.9, +0.4)
    check_visibility("c", (Vector2){+1.0, +0.0}, (Vector2){-0.9, +0.4});
    // d) 𝑎̅(+1.0, +0.0) and 𝑏̅(−0.8, −0.6)
    check_visibility("d", (Vector2){+1.0, +0.0}, (Vector2){-0.8, -0.6});
    // e) 𝑎̅(+1.0, +0.0) and 𝑏̅(−1.0, +0.1)
    check_visibility("e", (Vector2){+1.0, +0.0}, (Vector2){-1.0, +0.1});
    // f) 𝑎̅(+0.9, +0.1) and 𝑏̅(−0.9, −0.1)
    check_visibility("f", (Vector2){+0.9, +0.1}, (Vector2){-0.9, -0.1});
    return 0;
}
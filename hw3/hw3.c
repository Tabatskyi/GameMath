#include "hw3.h"

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

double cross2(Vector2 a, Vector2 b) {
    return (a.x * b.y) - (a.y * b.x);
}

Vector2 normalize2(Vector2 v) {
    double magnitude = mag2(v);
    if (double_is_zero(magnitude)) {
        return (Vector2){0.0, 0.0};
    }
    return (Vector2){v.x / magnitude, v.y / magnitude};
}

Vector2 add2(Vector2 a, Vector2 b) {
    return (Vector2){a.x + b.x, a.y + b.y};
}

Vector2 sub2(Vector2 a, Vector2 b) {
    return (Vector2){a.x - b.x, a.y - b.y};
}

Vector2 scale2(Vector2 v, double scalar) {
    return (Vector2){v.x * scalar, v.y * scalar};
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

bool ray_intersect(Vector2 origin, Vector2 direction, Vector2 A, Vector2 B, Vector2* out_hit) {
    Vector2 r = direction;
    Vector2 s = sub2(B, A);
    Vector2 q_p = sub2(A, origin);
    
    double r_cross_s = cross2(r, s);
    if (fabs(r_cross_s) < 1e-8) return false;
    
    double t = cross2(q_p, s) / r_cross_s;
    double u = cross2(q_p, r) / r_cross_s;
    
    if (t > 0.0001 && u >= 0.0 && u <= 1.0) {
        *out_hit = add2(origin, scale2(direction, t));
        return true;
    }
    return false;
}

Vector2 facing_normal(Vector2 A, Vector2 B, Vector2 direction) {
    Vector2 wall_vec = sub2(B, A);
    Vector2 n1 = normalize2((Vector2){-wall_vec.y, wall_vec.x});
    Vector2 n2 = normalize2((Vector2){wall_vec.y, -wall_vec.x});
    return (dot2(direction, n1) < 0) ? n1 : n2;
}

Vector2 reflection(Vector2 directory, Vector2 normal) {
    double dot = dot2(directory, normal);
    Vector2 reflection = sub2(directory, scale2(normal, 2.0 * dot));
    return normalize2(reflection);
}

double hit_angle(Vector2 directory, Vector2 normal) {
    Vector2 norm_dir = normalize2(directory);
    double dot = dot2(norm_dir, normal);
    return 90.0 - (acos(fabs(dot)) * (180.0 / M_PI));
}
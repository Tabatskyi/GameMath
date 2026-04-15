#include "hw3.h"

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

    printf("\n(3)\n");
    Vector2 A = {-3.0, -1.0}, B = {+4.0, +1.0}, C = {-1.0, +3.0}, S = {-2.0, +2.0}, D = {+1.0, -1.0}, hit1, hit2;
    char* filename = "data.txt";
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return 1;
    }
    fprintf(file, "A %.15f %.15f\n", A.x, A.y);
    fprintf(file, "B %.15f %.15f\n", B.x, B.y);
    fprintf(file, "C %.15f %.15f\n", C.x, C.y);
    fprintf(file, "S %.15f %.15f\n", S.x, S.y);
    fprintf(file, "D0 %.15f %.15f\n", D.x, D.y);
    printf("--- Console Output ---\n");
    if (ray_intersect(S, D, A, B, &hit1)) {
        fprintf(file, "H1 %.15f %.15f\n", hit1.x, hit1.y);
        
        Vector2 n1 = facing_normal(A, B, D);
        fprintf(file, "N1 %.15f %.15f\n", n1.x, n1.y);
        printf("d) Normal 1: (%.15f, %.15f)\nb) Angle 1: %.15f deg\n", n1.x, n1.y, hit_angle(D, n1));
        
        Vector2 D1 = reflection(D, n1);
        fprintf(file, "D1 %.15f %.15f\n", D1.x, D1.y);
        printf("f) Direction 1: (%.15f, %.15f)\n", D1.x, D1.y);
        
        if (ray_intersect(hit1, D1, B, C, &hit2)) {
            fprintf(file, "H2 %.15f %.15f\n", hit2.x, hit2.y);
            
            Vector2 n2 = facing_normal(B, C, D1);
            fprintf(file, "N2 %.15f %.15f\n", n2.x, n2.y);
            printf("e) Normal 2: (%.15f, %.15f)\nc) Angle 2: %.15f deg\n", n2.x, n2.y, hit_angle(D1, n2));
            
            Vector2 D2 = reflection(D1, n2);
            fprintf(file, "D2 %.15f %.15f\n", D2.x, D2.y);
            printf("g) Direction 2: (%.15f, %.15f)\n", D2.x, D2.y);
        }
    }
    
    fclose(file);
    printf("Data dumped to %s successfully.\n", filename);
    return 0;
}
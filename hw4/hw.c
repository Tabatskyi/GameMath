#include "hw.h"

Vector4 multiply_m4_v4(Matrix4 matrix, Vector4 vector) {
    Vector4 res;
    res.x = matrix.m[0][0] * vector.x + matrix.m[0][1] * vector.y + matrix.m[0][2] * vector.z + matrix.m[0][3] * vector.w;
    res.y = matrix.m[1][0] * vector.x + matrix.m[1][1] * vector.y + matrix.m[1][2] * vector.z + matrix.m[1][3] * vector.w;
    res.z = matrix.m[2][0] * vector.x + matrix.m[2][1] * vector.y + matrix.m[2][2] * vector.z + matrix.m[2][3] * vector.w;
    res.w = matrix.m[3][0] * vector.x + matrix.m[3][1] * vector.y + matrix.m[3][2] * vector.z + matrix.m[3][3] * vector.w;
    return res;
}

double determinant4(Matrix4 matrix) {
    return matrix.m[0][0] * (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1])
         - matrix.m[0][1] * (matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0])
         + matrix.m[0][2] * (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]);
}

void print_v4(const char* label, Vector4 v) {
    printf("%s (%.15f, %.15f, %.15f, %.15f)\n", label, v.x, v.y, v.z, v.w);
}

void print_m4(const char* label, Matrix4 matrix) {
    printf("%s:\n", label);
    for (int i = 0; i < 4; i++) {
        printf("  %.15f %.15f %.15f %.15f\n", matrix.m[i][0], matrix.m[i][1], matrix.m[i][2], matrix.m[i][3]);
    }
}

void dump_data(FILE* f, int id, const char* label, Vector4 v) {
    fprintf(f, "%d %s %.15f %.15f %.15f %.15f\n", id, label, v.x, v.y, v.z, v.w);
}

void solve(const int id, Matrix4 A, Vector4 a, Vector4 b, FILE* out_file) {
    double determinant = determinant4(A);
    printf("Determinant of A%d: %.15f\n", id, determinant);

    Vector4 a_res = multiply_m4_v4(A, a);
    Vector4 b_res = multiply_m4_v4(A, b);

    print_v4("a_orig", a);
    print_v4("b_orig", b);
    print_v4("a_res", a_res);
    print_v4("b_res", b_res);
    printf("\n");

    if (out_file) {
        dump_data(out_file, id, "a_orig", a);
        dump_data(out_file, id, "b_orig", b);
        dump_data(out_file, id, "a_res", a_res);
        dump_data(out_file, id, "b_res", b_res);
    }
}

int main() {
    const char* filename = "data.txt";
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file\n");
        return 1;
    }

    Vector4 a = {2.0, 1.0, 5.0, 0.0};
    Vector4 b = {2.0, 1.0, 5.0, 1.0};

    // 1) linear transformation matrix
    Matrix4 A1 = {{
        {1.0, 0.0, 0.0, 4.0},
        {0.0, 1.0, 0.0, 2.0},
        {0.0, 0.0, 1.0, 6.0},
        {0.0, 0.0, 0.0, 1.0}
    }};
    solve(1, A1, a, b, file);

    // 2) reflection matrix
    Matrix4 A2 = {{
        {-1.0, 0.0, 0.0, 4.0},
        {0.0, -1.0, 0.0, 2.0},
        {0.0, 0.0, -1.0, 6.0},
        {0.0, 0.0, 0.0, 1.0}
    }};
    solve(2, A2, a, b, file);

    // 3) rotation matrix
    Matrix4 A3 = {{
        {sqrt(2.0) / 2.0, -sqrt(2.0) / 2.0, 0.0, 4.0},
        {sqrt(2.0) / 2.0, sqrt(2.0) / 2.0, 0.0, 2.0},
        {0.0, 0.0, 1.0, 6.0},
        {0.0, 0.0, 0.0, 1.0}
    }};
    solve(3, A3, a, b, file);

    // 4) scaling matrix
    Matrix4 A4 = {{
        {0.5, 0.0, 0.0, 4.0},
        {0.0, 1.5, 0.0, 2.0},
        {0.0, 0.0, 1.0, 6.0},
        {0.0, 0.0, 0.0, 1.0}
    }};
    solve(4, A4, a, b, file);

    fclose(file);
    printf("Data successfully dumped to %s.\n", filename);
    return 0;
}
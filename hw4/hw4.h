#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "../hw1/hw1.c"

typedef struct {
    double x;
    double y;
    double z;
    double w;
} Vector4;

typedef struct {
    double m[4][4];
} Matrix4;

Vector4 multiply_m4_v4(Matrix4 matrix, Vector4 vector);
double determinant4(Matrix4 matrix);
void print_v4(const char* label, Vector4 v);
void print_m4(const char* label, Matrix4 matrix);
void dump_data(FILE* f, int id, const char* label, Vector4 v);
void solve(const int id, Matrix4 A, Vector4 a, Vector4 b, FILE* out_file);
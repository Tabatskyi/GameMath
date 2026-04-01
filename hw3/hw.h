#include <stdio.h>

typedef struct {
    double x;
    double y;
} Vector2;

typedef struct {
    double x;
    double y;
    double z;
} Vector3;

Vector3 add3(Vector3 a, Vector3 b);
Vector3 scale3(Vector3 v, double scalar);
double dot3(Vector3 a, Vector3 b);
void print_vector3(const char* label, Vector3 v);
#include <stdio.h>
#include <math.h>
#include "../hw1/Homework1.c"

#define M_PI 3.14159265358979323846

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

double mag2(Vector2 v);
double dot2(Vector2 a, Vector2 b);

void print_vector3(const char* label, Vector3 v);
void print_vector2(const char* label, Vector2 v);

double to_radians(double degrees);
double to_degrees(double radians);
double angle(Vector2 a, Vector2 b);

void check_visibility(char* label, Vector2 a, Vector2 b);
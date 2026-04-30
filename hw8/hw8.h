#ifndef HW8_H
#define HW8_H

#include "../hw1/hw1.h"
#include <math.h>
#include <float.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

constexpr int WIDTH = 1000;
constexpr int HEIGHT = 1000;

typedef struct {
    float x;
    float y;
} Point;

typedef struct {
    uint8_t r, g, b;
} Color;

enum DistanceMetric {
    EUCLIDEAN,
    COSINE,
    MANHATTAN
};

Color get_color(int index);
float calculate_distance(float x1, float y1, float x2, float y2, enum DistanceMetric metric);
void generate_voronoi(const Point* spots, int num_spots, enum DistanceMetric metric, const char* filename);
int load_points_from_json(const char* path, Point** out_points, int* out_count);

#endif
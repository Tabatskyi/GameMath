#include "hw8.h"

Color get_color(int index) {
    uint32_t hash = (index * 2654435761U);
    return (Color){
        (uint8_t)((hash >> 16) & 0xFF),
        (uint8_t)((hash >> 8) & 0xFF),
        (uint8_t)(hash & 0xFF)
    };
}

float calculate_distance(float x1, float y1, float x2, float y2, enum DistanceMetric metric) {
    if (metric == EUCLIDEAN) {
        float dx = x1 - x2;
        float dy = y1 - y2;

        return dx * dx + dy * dy; 
    } else if (metric == COSINE) {
        float dot_product = (x1 * x2) + (y1 * y2);
        float mag1 = sqrtf(x1 * x1 + y1 * y1);
        float mag2 = sqrtf(x2 * x2 + y2 * y2);
        
        if (float_is_zero(mag1) || float_is_zero(mag2)) return 1.0f; 
        
        return 1.0f - (dot_product / (mag1 * mag2));
    } else {
        return float_abs(x1 - x2) + float_abs(y1 - y2);
    }
}

void generate_voronoi(const Point* spots, int num_spots, enum DistanceMetric metric, const char* filename) {
    auto img = (Color*)malloc(WIDTH * HEIGHT * sizeof(Color));
    if (!img) {
        fprintf(stderr, "Memory allocation failed!\n");
        return;
    }
    
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            float min_dist = FLT_MAX;
            int best_spot = -1;
            
            for (int i = 0; i < num_spots; ++i) {
                float dist = calculate_distance((float)x, (float)y, spots[i].x, spots[i].y, metric);
                if (float_less(dist, min_dist)) {
                    min_dist = dist;
                    best_spot = i;
                }
            }
            img[y * WIDTH + x] = get_color(best_spot);
        }
    }
    
    for (int i = 0; i < num_spots; ++i) {
        int sx = (int)spots[i].x;
        int sy = (int)spots[i].y;
        for (int dy = -3; dy <= 3; ++dy) {
            for (int dx = -3; dx <= 3; ++dx) {
                int px = sx + dx;
                int py = sy + dy;
                if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT) {
                    img[py * WIDTH + px] = (Color){0, 0, 0};
                }
            }
        }
    }

    FILE *f = fopen(filename, "wb");
    if (f) {
        fprintf(f, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
        fwrite(img, sizeof(Color), WIDTH * HEIGHT, f);
        fclose(f);
    } else {
        fprintf(stderr, "Failed to open file %s for writing\n", filename);
    }
    
    free(img);
}

static char* read_file_to_buffer(const char* path, long* out_size) {
    if (out_size) {
        *out_size = 0;
    }

    FILE* f = fopen(path, "rb");
    if (!f) {
        return NULL;
    }

    if (fseek(f, 0, SEEK_END) != 0) {
        fclose(f);
        return NULL;
    }

    long size = ftell(f);
    if (size <= 0) {
        fclose(f);
        return NULL;
    }

    if (fseek(f, 0, SEEK_SET) != 0) {
        fclose(f);
        return NULL;
    }

    char* buffer = (char*)malloc((size_t)size + 1u);
    if (!buffer) {
        fclose(f);
        return NULL;
    }

    size_t read_count = fread(buffer, 1u, (size_t)size, f);
    fclose(f);

    if ((long)read_count != size) {
        free(buffer);
        return NULL;
    }

    buffer[size] = '\0';
    if (out_size) {
        *out_size = size;
    }
    return buffer;
}

int load_points_from_json(const char* path, Point** out_points, int* out_count) {
    if (!path || !out_points || !out_count) {
        return -1;
    }

    *out_points = NULL;
    *out_count = 0;

    long size = 0;
    char* buffer = read_file_to_buffer(path, &size);
    if (!buffer) {
        return -1;
    }

    int capacity = 16;
    int count = 0;
    Point* points = (Point*)malloc((size_t)capacity * sizeof(Point));
    if (!points) {
        free(buffer);
        return -1;
    }

    int parse_error = 0;
    const char* cursor = buffer;
    while ((cursor = strstr(cursor, "\"x\"")) != NULL) {
        const char* colon = strchr(cursor, ':');
        if (!colon) {
            parse_error = 1;
            break;
        }

        char* endptr = NULL;
        float x = strtof(colon + 1, &endptr);
        if (endptr == colon + 1 || !float_is_finite(x)) {
            parse_error = 1;
            break;
        }

        const char* ykey = strstr(endptr, "\"y\"");
        if (!ykey) {
            parse_error = 1;
            break;
        }

        colon = strchr(ykey, ':');
        if (!colon) {
            parse_error = 1;
            break;
        }

        float y = strtof(colon + 1, &endptr);
        if (endptr == colon + 1 || !float_is_finite(y)) {
            parse_error = 1;
            break;
        }

        if (count >= capacity) {
            int new_capacity = capacity * 2;
            Point* resized = (Point*)realloc(points, (size_t)new_capacity * sizeof(Point));
            if (!resized) {
                parse_error = 1;
                break;
            }
            points = resized;
            capacity = new_capacity;
        }

        points[count++] = (Point){x, y};
        cursor = endptr;
    }

    free(buffer);

    if (parse_error || count == 0) {
        free(points);
        return -1;
    }

    *out_points = points;
    *out_count = count;
    return 0;
}
#include "hw8.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Point* spots = NULL;
    int num_spots = 0;
    const char* json_path = "spots.json";

    if (load_points_from_json(json_path, &spots, &num_spots) != 0) {
        json_path = "hw8/spots.json";
        if (load_points_from_json(json_path, &spots, &num_spots) != 0) {
            fprerrf(stderr, "Failed to load spots from spots.json or hw8/spots.json\n");
            return 1;
        }
    } 
    
    printf("Generating Voronoi diagrams for %d spots at %dx%d resolution...\n", num_spots, WIDTH, HEIGHT);
    
    generate_voronoi(spots, num_spots, EUCLIDEAN, "voronoi_euclidean.ppm");
    printf("Saved: voronoi_euclidean.ppm\n");
    
    generate_voronoi(spots, num_spots, MANHATTAN, "voronoi_manhattan.ppm");
    printf("Saved: voronoi_manhattan.ppm\n");

    generate_voronoi(spots, num_spots, COSINE, "voronoi_cosine.ppm");
    printf("Saved: voronoi_cosine.ppm\n");

    free(spots);
    return 0;
}
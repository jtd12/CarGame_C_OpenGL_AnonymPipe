#include"functions.h"

float random_float(float min, float max) {
    // Scale rand() result to the range [min, max]
    return min + (float)rand() / (float)(RAND_MAX / (max - min));
}


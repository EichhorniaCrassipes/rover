#include "PerlinNoise.h"

#include <algorithm>
#include <cmath>
#include <random>

using std::default_random_engine;
using std::shuffle;
using std::floor;


generator::PerlinNoise::PerlinNoise(const long long seed) {
    permutation.resize(256);
    for (unsigned short i = 0; i < 256; i++) {
        permutation[i] = i;
    }

    default_random_engine engine(seed);
    shuffle(permutation.begin(), permutation.end(), engine);

    permutation.insert(permutation.end(), permutation.begin(), permutation.end());
}

double generator::PerlinNoise::fade(const double t) {
    return t * t * t * (t * (t * 6. - 15.) + 10.);
}
double generator::PerlinNoise::interpolation(const double t, const double a, const double b) {
    return a + t * (b - a);
}
double generator::PerlinNoise::gradient(const int hash, const double x, const double y) {
    const int h = hash & 7;
    const double u = h < 4 ? x : y,
                 v = h < 4 ? y : x;
    return (h & 1 ? -u : u) + (h & 2 ? -2. * v : 2. * v);
}

double generator::PerlinNoise::noise(double x, double y) const {
    const int X = static_cast<int>(floor(x)) & 255,
              Y = static_cast<int>(floor(y)) & 255;

    x -= floor(x);
    y -= floor(y);

    const double u = fade(x),
                 v = fade(y);

    const int A = permutation[X] + Y,
              B = permutation[X + 1] + Y;

    return .5 * (1. + interpolation(
        v,
        interpolation(
            u,
            gradient(permutation[A], x, y),
            gradient(permutation[B], x - 1, y)
            ),
        interpolation(
            u,
            gradient(permutation[A + 1], x, y - 1),
            gradient(permutation[B + 1], x - 1, y - 1)
            )
    ));
}

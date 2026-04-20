#ifndef PERLIN_NOISE
#define PERLIN_NOISE

#include <vector>
using std::vector;

#include <random>
using std::default_random_engine;

namespace generator {
    class PerlinNoise {
    public:
        explicit PerlinNoise(default_random_engine* engine_link);
        ~PerlinNoise() = default;

        [[nodiscard]] double noise(double x, double y) const;

    private:
        default_random_engine* engine;
        vector<int> permutation;

        static double fade(double t);
        static double interpolation(double t, double a, double b);
        static double gradient(int hash, double x, double y);
    };
}

#endif
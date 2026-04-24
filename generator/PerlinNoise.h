#ifndef PERLIN_NOISE
#define PERLIN_NOISE

#include <vector>
using std::vector;

#include <random>
using std::mt19937;

namespace generator {
    class PerlinNoise {
    public:
        explicit PerlinNoise(mt19937* engine_link);
        ~PerlinNoise() = default;

        [[nodiscard]] double noise(double x, double y) const;

    private:
        mt19937* engine;
        vector<int> permutation;

        static double fade(double t);
        static double interpolation(double t, double a, double b);
        static double gradient(int hash, double x, double y);
    };
}

#endif
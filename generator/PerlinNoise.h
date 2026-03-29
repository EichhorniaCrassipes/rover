#ifndef PERLIN_NOISE
#define PERLIN_NOISE

#include <vector>
using std::vector;

namespace generator {
    class PerlinNoise {
    public:
        explicit PerlinNoise(long long seed);
        ~PerlinNoise() = default;

        [[nodiscard]] double noise(double x, double y) const;

    private:
        vector<int> permutation;

        static double fade(double t);
        static double interpolation(double t, double a, double b);
        static double gradient(int hash, double x, double y);
    };
}

#endif
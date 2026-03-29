#ifndef MAP_GENERATOR
#define MAP_GENERATOR

#include "PerlinNoise.h"

#include <vector>
using std::vector;

#include <limits>
using std::numeric_limits;

namespace generator {
    class MapGenerator {
    public:
        explicit MapGenerator(long long seed, size_t world_size = numeric_limits<size_t>::max());
        ~MapGenerator();

        [[nodiscard]] double get_tile(size_t x, size_t y) const;

    private:
        PerlinNoise* noise;
        double world_size;
    };
}

#endif
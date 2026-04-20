#ifndef MAP_GENERATOR
#define MAP_GENERATOR

#include "PerlinNoise.h"
#include "tile.h"

#include <vector>
using std::vector;

#include <array>
using std::array;


namespace generator {
    class MapGenerator {
    public:
        explicit MapGenerator(long long seed);
        ~MapGenerator();

        [[nodiscard]] Tile get_tile(size_t x, size_t y) const;

        void reseed(long long new_seed);
    private:
        double STRETCH = 10;
        size_t COORD_SHIFT = 100000;

        float TILE_VARIATION_MULTIPLIER = 4,
              DECORATION_VARIATION_MULTIPLIER = 8,
              DECORATION_MAX_OFFSET = 1.5;

        long long initial_seed;
        array<default_random_engine*, 4> random_engines{};
        default_random_engine* variation;
        PerlinNoise *temperature, *humidity, *height;
        void free_memory() const;

        void reseed_variations(size_t x, size_t y) const;

        double get_tile_noise_value(double x, double y, unsigned char octaves, const PerlinNoise* noise) const;

        [[nodiscard]] long long seed_shift(unsigned shift) const;
    };
}

#endif
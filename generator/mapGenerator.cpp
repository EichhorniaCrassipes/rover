#include "mapGenerator.h"


generator::MapGenerator::MapGenerator(const long long seed, const size_t world_size) {
    noise = new PerlinNoise(seed);
    this->world_size = static_cast<double>(world_size);
}
generator::MapGenerator::~MapGenerator() {
    delete noise;
}

double generator::MapGenerator::get_tile(const size_t x, const size_t y) const {
    const double relative_x = static_cast<double>(x) / world_size,
                 relative_y = static_cast<double>(y) / world_size;
    return noise->noise(relative_x, relative_y);
}

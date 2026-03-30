#include "mapGenerator.h"

#include <random>
using std::default_random_engine;
using std::uniform_int_distribution;

#include <string>
using std::string;


generator::MapGenerator::MapGenerator(const long long seed, const size_t world_size) {
    temperature = new PerlinNoise(seed);
    humidity = new PerlinNoise(seed_shift(1));
    height = new PerlinNoise(seed_shift(2));
    this->seed = seed;
    this->world_size = static_cast<double>(world_size);
}
generator::MapGenerator::~MapGenerator() {
    delete temperature;
    delete humidity;
}


double generator::MapGenerator::get_tile(const size_t x, const size_t y) const {
    const double relative_x = static_cast<double>(x) / world_size,
                 relative_y = static_cast<double>(y) / world_size;
    const auto te = temperature->noise(relative_x, relative_y),
               hu = humidity->noise(relative_x, relative_y),
               he = height->noise(relative_x, relative_y);
    return te + hu + he;  // здесь определение биома и высоты по параметрам
}

long long generator::MapGenerator::seed_shift(const unsigned shift) const {
    default_random_engine random(seed);

    for (unsigned i = 0; i < shift; i++) random();

    string seed_string;
    long long tmp = seed;

    while (tmp > 0 && seed_string.length() < 20) {
        auto digit = static_cast<int>(tmp % 10);
        if (digit < 0) digit = -digit;

        seed_string += static_cast<char>(48 + digit);
        tmp /= 10;
    }

    uniform_int_distribution dist(1, 99);
    const int random_value = dist(random);

    constexpr std::hash<std::string> hasher;
    return static_cast<long long>(hasher(seed_string) / random_value);
}

#include "mapGenerator.h"

#include <random>
using std::default_random_engine;
using std::uniform_int_distribution;

#include <string>
using std::string;


generator::MapGenerator::MapGenerator(const long long seed, const size_t world_size) {
    this->seed = seed;
    this->world_size = static_cast<double>(world_size);

    temperature = new PerlinNoise(seed);
    humidity = new PerlinNoise(seed_shift(1));
    height = new PerlinNoise(seed_shift(2));
}
generator::MapGenerator::~MapGenerator() {
    delete temperature;
    delete humidity;
    delete height;
}


double generator::MapGenerator::get_tile(const size_t x, const size_t y) const {
    const double relative_x = static_cast<double>(x) / world_size,
                 relative_y = static_cast<double>(y) / world_size;

    const double te = get_tile_noise_value(relative_x, relative_y, 4, temperature),
                 hu = get_tile_noise_value(relative_x, relative_y, 2, humidity),
                 he = get_tile_noise_value(relative_x, relative_y, 2, height);

    return te + hu + he;  // здесь определение биома и высоты по параметрам
}
double generator::MapGenerator::get_tile_noise_value(const double x, const double y, const unsigned char octaves, const PerlinNoise* noise) const {
    const double xn = x / STRETCH,
                 yn = y / STRETCH;

    double value = 0,
           sum   = 0;

    for (unsigned char octave = 0; octave < octaves; octave++) {
        const auto k = 1l << octave;
        sum += 1. / k;
        value += noise->noise(xn * k, yn * k) / k;
    }

    return value / sum;
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

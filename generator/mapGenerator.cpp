#include "mapGenerator.h"

#include "biomes.h"
#include "deposits.h"
#include "decorations.h"

#include <random>
using std::default_random_engine;
using std::uniform_int_distribution;

#include <string>
using std::string;


generator::MapGenerator::MapGenerator(const long long seed) {
    this->seed = seed;
    temperature = new PerlinNoise(seed);
    humidity = new PerlinNoise(seed_shift(1));
    height = new PerlinNoise(seed_shift(2));
    variation = new PerlinNoise(seed_shift(3));
}
generator::MapGenerator::~MapGenerator() { free_noises_memory(); }

void generator::MapGenerator::free_noises_memory() const {
    delete temperature;
    delete humidity;
    delete height;
    delete variation;
}


generator::Tile generator::MapGenerator::get_tile(const size_t x, const size_t y) const {
    const auto relative_x = static_cast<double>(x + COORD_SHIFT),
               relative_y = static_cast<double>(y + COORD_SHIFT);

    const double te = get_tile_noise_value(relative_x, relative_y, 4, temperature),
                 hu = get_tile_noise_value(relative_x, relative_y, 2, humidity),
                 he = get_tile_noise_value(relative_x, relative_y, 2, height),
                 va = variation->noise(relative_x, relative_y);

    Tile tile;
    tile.variation = static_cast<unsigned char>(va * TILE_VARIATION_MULTIPLIER);
    tile.decoration = {"", 0};

    for (const auto &b : GLOBAL_BIOMES)
        if (b.temperature_low <= te && te <= b.temperature_high &&
               b.humidity_low <= hu && hu <= b.humidity_high) {
            tile.biome = b.name;
            break;
        }
    for (const auto &d : GLOBAL_DEPOSITS)
        if (d.temperature_low <= te && te <= d.temperature_high &&
               d.humidity_low <= hu && hu <= d.humidity_high &&
                 d.height_low <= he && he <= d.height_high) {
            tile.deposit = d.name;
            break;
        }
    for (const auto &d : GLOBAL_DECORATIONS)
        if (d.temperature_low <= te && te <= d.temperature_high &&
               d.humidity_low <= hu && hu <= d.humidity_high &&
                 d.height_low <= he && he <= d.height_high) {
            tile.decoration = {
                d.name,
                static_cast<unsigned char>(va * DECORATION_VARIATION_MULTIPLIER)
            };
            break;
        }

    return tile;
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

void generator::MapGenerator::reseed(const long long new_seed) {
    seed = new_seed;
    free_noises_memory();
    temperature = new PerlinNoise(seed);
    humidity = new PerlinNoise(seed_shift(1));
    height = new PerlinNoise(seed_shift(2));
    variation = new PerlinNoise(seed_shift(3));
}

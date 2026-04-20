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
    random_engines[0] = new default_random_engine(seed);
    random_engines[1] = new default_random_engine(seed_shift(1));
    random_engines[2] = new default_random_engine(seed_shift(2));
    random_engines[3] = new default_random_engine(seed_shift(3));
    variation = random_engines[3];

    this->initial_seed = seed;

    temperature = new PerlinNoise(random_engines[0]);
    humidity = new PerlinNoise(random_engines[1]);
    height = new PerlinNoise(random_engines[2]);
}
generator::MapGenerator::~MapGenerator() { free_memory(); }

void generator::MapGenerator::free_memory() const {
    delete temperature;
    delete humidity;
    delete height;
    for (const auto r : random_engines)
        delete r;
}


generator::Tile generator::MapGenerator::get_tile(const size_t x, const size_t y) const {
    const auto relative_x = static_cast<double>(x + COORD_SHIFT),
               relative_y = static_cast<double>(y + COORD_SHIFT);

    const double te = get_tile_noise_value(relative_x, relative_y, 4, temperature),
                 hu = get_tile_noise_value(relative_x, relative_y, 2, humidity),
                 he = get_tile_noise_value(relative_x, relative_y, 2, height);
    const auto v1 = static_cast<float>((*variation)()),
               v2 = static_cast<float>((*variation)());

    Tile tile;
    tile.variation = static_cast<unsigned char>(v1 * TILE_VARIATION_MULTIPLIER);
    tile.decorations = {};

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
            tile.decorations.push_back({
                d.name,
                {(v1 - .5f) * 2.f * DECORATION_MAX_OFFSET, (v2 - .5f) * 2.f * DECORATION_MAX_OFFSET},
                static_cast<unsigned char>(v1 * DECORATION_VARIATION_MULTIPLIER)
            });
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
    default_random_engine random(initial_seed);

    for (unsigned i = 0; i < shift; i++) random();

    string seed_string;
    long long tmp = initial_seed;

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
    free_memory();

    initial_seed = new_seed;

    random_engines[0] = new default_random_engine(new_seed);
    random_engines[1] = new default_random_engine(seed_shift(1));
    random_engines[2] = new default_random_engine(seed_shift(2));
    random_engines[3] = new default_random_engine(seed_shift(3));

    temperature = new PerlinNoise(random_engines[0]);
    humidity = new PerlinNoise(random_engines[1]);
    height = new PerlinNoise(random_engines[2]);
}

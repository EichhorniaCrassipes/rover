#include "mapGenerator.h"

#include "config/biomes.h"
#include "config/deposits.h"
#include "config/decorations.h"

#include <iostream>


generator::MapGenerator::MapGenerator(const long long seed) { reseed(seed); }
generator::MapGenerator::~MapGenerator() { free_memory(); }

void generator::MapGenerator::free_memory() const {
    delete temperature;
    delete humidity;
    delete height;
    delete deposit;
    for (const auto r : random_engines)
        delete r;
}

void generator::MapGenerator::local_variation_engine_reseed(const long long x, const long long y) const {
    array<seed_seq::result_type, 3> seeds = {
        static_cast<seed_seq::result_type>(initial_seed),
        static_cast<seed_seq::result_type>(x),
        static_cast<seed_seq::result_type>(y)
    };
    seed_seq seq(seeds.begin(), seeds.end());

    array<seed_seq::result_type, 1> final_seed{};
    seq.generate(final_seed.begin(), final_seed.end());

    variation->seed(final_seed[0]);
}


generator::Tile generator::MapGenerator::get_tile(const long long x, const long long y) {
    const auto shifted_x = static_cast<double>(x + COORD_SHIFT),
               shifted_y = static_cast<double>(y + COORD_SHIFT);

    const double te = get_tile_noise_value(
                     shifted_x,
                     shifted_y,
                     8, temperature
                 ),
                 hu = get_tile_noise_value(
                     shifted_x,
                     shifted_y,
                     4, humidity
                 ),
                 he = get_tile_noise_value(
                     shifted_x * STRETCH_v2,
                     shifted_y * STRETCH_v2,
                     4, height
                 ),
                 de = get_tile_noise_value(
                     shifted_x * STRETCH_v2,
                     shifted_y * STRETCH_v2,
                     4, deposit
                 );
    local_variation_engine_reseed(x, y);
    normal_distribution.reset();
    const auto v1 = normal_distribution(*variation),
               v2 = normal_distribution(*variation);

    Tile tile;
    tile.variation = static_cast<unsigned char>(v1 * TILE_VARIATION_MULTIPLIER);
    tile.decorations = {};

    for (const auto &[
                        name,
                        temperature_low,
                        temperature_high,
                        humidity_low,
                        humidity_high
                     ] : GLOBAL_BIOMES)
        if (temperature_low <= te && te <= temperature_high &&
               humidity_low <= hu && hu <= humidity_high) {
            tile.biome = name;
            break;
        }
    for (const auto &[
                        name,
                        temperature_low,
                        temperature_high,
                        humidity_low,
                        humidity_high,
                        deposit_low,
                        deposit_high
                     ] : GLOBAL_DEPOSITS)
        if (temperature_low <= te && te <= temperature_high &&
               humidity_low <= hu && hu <= humidity_high &&
                deposit_low <= de && de <= deposit_high) {
            tile.deposit = name;
            break;
        }
    for (const auto &[
                        name,
                        temperature_low,
                        temperature_high,
                        humidity_low,
                        humidity_high,
                        height_low,
                        height_high
                     ] : GLOBAL_DECORATIONS)
        if (temperature_low <= te && te <= temperature_high &&
               humidity_low <= hu && hu <= humidity_high &&
                 height_low <= he && he <= height_high) {
            tile.decorations.push_back({
                name,
                Vector2f{v1 - .5f, v2 - .5f} * 2.f * DECORATION_MAX_OFFSET,
                static_cast<unsigned char>(v1 * DECORATION_VARIATION_MULTIPLIER)
            });
            break;
        }

    return tile;
}
double generator::MapGenerator::get_tile_noise_value(const double x, const double y, const unsigned char octaves, const PerlinNoise* noise) const {
    const double xn = x * STRETCH,
                 yn = y * STRETCH;

    double value = 0,
           sum   = 0;

    for (unsigned char octave = 0; octave < octaves; octave++) {
        const long k = 1l << octave;
        sum += 1. / k;
        value += noise->noise(xn * k, yn * k) / k;
    }

    return value / sum;
}

long long generator::MapGenerator::seed_shift(const unsigned shift) const {
    mt19937 random(initial_seed);

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

    constexpr std::hash<string> hasher;
    return static_cast<long long>(hasher(seed_string) / random_value);
}

void generator::MapGenerator::reseed(const long long new_seed) {
    free_memory();

    initial_seed = new_seed;

    random_engines[0] = new mt19937(new_seed);
    random_engines[1] = new mt19937(seed_shift(1));
    random_engines[2] = new mt19937(seed_shift(2));
    random_engines[3] = new mt19937(seed_shift(3));
    random_engines[4] = new mt19937(0);
    variation = random_engines[4];

    temperature = new PerlinNoise(random_engines[0]);
    humidity = new PerlinNoise(random_engines[1]);
    height = new PerlinNoise(random_engines[2]);
    deposit = new PerlinNoise(random_engines[3]);
}

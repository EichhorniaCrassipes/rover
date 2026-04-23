#ifndef BIOMES
#define BIOMES 4

#include <string>
using std::string;

#include <array>
using std::array;


namespace generator {
    struct Biome {
        string name;
        double temperature_low, temperature_high,
               humidity_low, humidity_high;
    };

    extern array<Biome, BIOMES> GLOBAL_BIOMES;
}

#endif

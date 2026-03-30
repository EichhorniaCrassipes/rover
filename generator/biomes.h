#ifndef BIOMES
#define BIOMES

#include <string>
using std::string;

namespace generator {
    struct Biome {
        string name;
        double temperature_low, temperature_high,
               humidity_low, humidity_high;
    };

    extern Biome GLOBAL_BIOMES[3];
}

#endif
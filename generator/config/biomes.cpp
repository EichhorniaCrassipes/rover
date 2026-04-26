#include "biomes.h"
using generator::Biome;


array<Biome, BIOMES> generator::GLOBAL_BIOMES = {
    Biome{"test0", 0.55, 1, 0, 1},
    Biome{"test1", 0, 0.55, 0.55, 1},
    Biome{"test2", 0, 0.55, 0, 0.55},
};

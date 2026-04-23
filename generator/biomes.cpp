#include "biomes.h"
using generator::Biome;


array<Biome, BIOMES> generator::GLOBAL_BIOMES = {
    Biome{"test0", 0.5, 0.8, 0, 1},
    Biome{"test1", 0.3, 0.5, 0, 1},
    Biome{"test2", 0, 0.3, 0, 1},
    Biome{"test2", 0.8, 1, 0, 1},
};

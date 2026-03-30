#ifndef GENERATOR_TILE
#define GENERATOR_TILE

#include <string>
using std::string;

namespace generator {
    struct Tile {
        unsigned char variation;
        string biome, deposit;
    };
}

#endif
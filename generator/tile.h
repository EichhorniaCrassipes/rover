#ifndef GENERATOR_TILE
#define GENERATOR_TILE

#include <string>
using std::string;

namespace generator {
    struct TileDecoration {
        string name;
        unsigned char variation;
    };

    struct Tile {
        unsigned char variation;
        string biome, deposit;
        TileDecoration decoration;
    };
}

#endif
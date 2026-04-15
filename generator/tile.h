#ifndef GENERATOR_TILE
#define GENERATOR_TILE

#include <string>
using std::string;

namespace generator {
    struct TileDecoration {
        string name;
        double offset_x, offset_y;
        unsigned char variation;
    };

    struct Tile {
        unsigned char variation;
        string biome, deposit;
        TileDecoration decoration;
    };
}

#endif
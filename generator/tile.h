#ifndef GENERATOR_TILE
#define GENERATOR_TILE

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <SFML/System/Vector2.hpp>
using sf::Vector2f;

namespace generator {
    struct TileDecoration {
        string name;
        Vector2f offset;
        unsigned char variation;
    };

    struct Tile {
        unsigned char variation;
        string biome, deposit;
        vector<TileDecoration> decorations;
    };
}

#endif
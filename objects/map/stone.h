#ifndef ROVER_STONE_H
#define ROVER_STONE_H

#include "block.h"

#include <string>
using std::string;

namespace object {
    class Stone : public Block {
    public:
        Stone(Vector2f pos, const string &biome, unsigned char variation = 0);
        ~Stone() override = default;
    };
}

#endif

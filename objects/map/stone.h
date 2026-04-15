#ifndef ROVER_STONE_H
#define ROVER_STONE_H
#include "block.h"
#include <string>
using std::string;

class Stone : public object::Block
{
public:
    Stone(sf::Vector2f pos,string biome, char variation);
    ~Stone() = default;

};

#endif //ROVER_STONE_H
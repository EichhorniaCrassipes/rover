#ifndef ROVER_STONE_H
#define ROVER_STONE_H
#include "block.h"
#include <string>
using std::string;

class Stone : public object::Block
{
public:
    Stone(string biome, char variation = 0);
    ~Stone();

};

#endif //ROVER_STONE_H
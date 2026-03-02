#ifndef ROVER_BLOCK_H
#define ROVER_BLOCK_H
#include "mapElement.h"

class Block : public MapElement
{
    public:
    Block();
    ~Block();
protected:
    sf::vector2f hitbox;
};


#endif //ROVER_BLOCK_H
#ifndef ROVER_BLOCK_H
#define ROVER_BLOCK_H
#include "mapElement.h"

class Block : public MapElement
{
public:
    Block();
    ~Block() override;
protected:
    sf::Vector2f hitbox;
};


#endif
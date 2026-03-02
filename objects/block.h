#ifndef ROVER_BLOCK_H
#define ROVER_BLOCK_H
#include "mapElement.h"

#include <SFML/Graphics.hpp>

#include <iostream>
using namespace std;

class Block : public MapElement
{
public:
    Block();
    static void say();
    ~Block() override;
protected:
    sf::Vector2f hitbox;
};


#endif //ROVER_BLOCK_H
#ifndef ROVER_BLOCK_H
#define ROVER_BLOCK_H
#include "mapElement.h"

#include <iostream>
using namespace std;

class Block : public MapElement
{
public:
    Block() : MapElement()
    {
        cout << "[Block] created!" << endl;
    }
    static void say()
    {
        cout << "[Block] some text!" << endl;
    }
    ~Block()
    {
        cout << "[Block] deleted!" << endl;
    }
protected:
    sf::vector2f hitbox;
};


#endif //ROVER_BLOCK_H
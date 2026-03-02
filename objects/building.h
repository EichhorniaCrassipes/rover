#ifndef ROVER_BUILDING_H
#define ROVER_BUILDING_H
#include "block.h"

#include <iostream>
using namespace std;

class Building : public Block
{
public:
    Building() : Block()
    {
        cout << "[Building] created!" << endl;
    }
    static void say()
    {
        cout << "[Building] some text!" << endl;
    }
    ~Building()
    {
        cout << "[Building] deleted!" << endl;
    }
};

#endif //ROVER_BUILDING_H
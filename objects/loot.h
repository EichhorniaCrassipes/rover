#ifndef ROVER_LOOT_H
#define ROVER_LOOT_H
#include "block.h"

#include <iostream>
using namespace std;

class Loot : public Block
{
public:
    Loot() : Block()
    {
        cout << "[Loot] created!" << endl;
    }
    static void say()
    {
        cout << "[Loot] some text!" << endl;
    }
    ~Loot()
    {
        cout << "[Loot] deleted!" << endl;
    }
};

#endif //ROVER_LOOT_H
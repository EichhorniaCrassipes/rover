#ifndef ROVER_CHEST_H
#define ROVER_CHEST_H
#include "block.h"

#include <iostream>
using namespace std;

class Chest : public Block
{
public:
    Chest() : Block()
    {
        cout << "[Chest] created!" << endl;
    }
    static void say()
    {
        cout << "[Chest] some text!" << endl;
    }
    ~Chest()
    {
        cout << "[Chest] deleted!" << endl;
    }
};

#endif //ROVER_CHEST_H
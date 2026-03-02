#ifndef ROVER_ENEMY_H
#define ROVER_ENEMY_H
#include "mob.h"

#include <iostream>
using namespace std;

class Enemy : public Mob
{
public:
    Enemy() : Mob()
    {
        cout << "[Enemy] created!" << endl;
    }
    static void say()
    {
        cout << "[Enemy] some text!" << endl;
    }
    ~Enemy()
    {
        cout << "[Enemy] deleted!" << endl;
    }
};

#endif //ROVER_ENEMY_H
#ifndef ROVER_MOB_H
#define ROVER_MOB_H
#include "entity.h"

#include <iostream>
using namespace std;

class Mob : public Entity
{
public:
    Mob() : Entity()
    {
        cout << "[Mob] created" << endl;
    }
    static void say()
    {
        cout << "[Mob] some text!" << endl;
    }
    ~Mob()
    {
        cout << "[Mob] deleted!" << endl;
    }
};

#endif //ROVER_MOB_H
#ifndef ROVER_MOB_H
#define ROVER_MOB_H
#include "entity.h"

#include <iostream>
using namespace std;

class Mob : public Entity
{
public:
    Mob();
    static void say();
    ~Mob() override;
};

#endif //ROVER_MOB_H
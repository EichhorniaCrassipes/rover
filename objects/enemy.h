#ifndef ROVER_ENEMY_H
#define ROVER_ENEMY_H
#include "mob.h"

#include <iostream>
using namespace std;

class Enemy : public Mob
{
public:
    Enemy();
    static void say();
    ~Enemy() override;
};

#endif //ROVER_ENEMY_H
#ifndef ROVER_PLAYER_H
#define ROVER_PLAYER_H
#include "mob.h"

#include <iostream>
using namespace std;

class Player : public Mob
{
public:
    Player();
    static void say();
    ~Player() override;
};

#endif //ROVER_PLAYER_H
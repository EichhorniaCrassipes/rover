#ifndef ROVER_NPC_H
#define ROVER_NPC_H
#include "entity.h"

#include <iostream>
using namespace std;

class NPC : public Entity
{
public:
    NPC();
    static void say();
    ~NPC() override;
};

#endif //ROVER_NPC_H
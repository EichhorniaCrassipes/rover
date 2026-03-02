#ifndef ROVER_LOOT_H
#define ROVER_LOOT_H
#include "block.h"

#include <iostream>
using namespace std;

class Loot : public Block
{
public:
    Loot();
    static void say();
    ~Loot() override;
};

#endif //ROVER_LOOT_H
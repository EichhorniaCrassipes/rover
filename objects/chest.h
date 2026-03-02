#ifndef ROVER_CHEST_H
#define ROVER_CHEST_H
#include "block.h"

#include <iostream>
using namespace std;

class Chest : public Block
{
public:
    Chest();
    static void say();
    ~Chest() override;
};

#endif //ROVER_CHEST_H
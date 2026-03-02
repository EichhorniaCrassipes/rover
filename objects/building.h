#ifndef ROVER_BUILDING_H
#define ROVER_BUILDING_H

#include "block.h"
#include <iostream>

class Building : public Block
{
public:
    Building();
    static void say();
    ~Building() override;
};

#endif // ROVER_BUILDING_H
#include "building.h"

Building::Building()
{
    std::cout << "[Building] created!" << std::endl;
}

void Building::say()
{
    std::cout << "[Building] some text!" << std::endl;
}

Building::~Building()
{
    std::cout << "[Building] deleted!" << std::endl;
}
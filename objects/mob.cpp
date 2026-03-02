#include "mob.h"

Mob::Mob()
{
    std::cout << "[Mob] created!" << std::endl;
}

void Mob::say()
{
    std::cout << "[Mob] some text!" << std::endl;
}

Mob::~Mob()
{
    std::cout << "[Mob] deleted!" << std::endl;
}

#include "loot.h"

Loot::Loot()
{
    std::cout << "[Loot] created!" << std::endl;
}

void Loot::say()
{
    std::cout << "[Loot] some text!" << std::endl;
}

Loot::~Loot()
{
    std::cout << "[Loot] deleted!" << std::endl;
}

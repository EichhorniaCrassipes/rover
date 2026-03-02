#include "chest.h"

Chest::Chest()
{
    std::cout << "[Chest] created!" << std::endl;
}

void Chest::say()
{
    std::cout << "[Chest] some text!" << std::endl;
}

Chest::~Chest()
{
    std::cout << "[Chest] deleted!" << std::endl;
}


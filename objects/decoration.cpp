#include "decoration.h"

Decoration::Decoration()
{
    std::cout << "[Decoration] created!" << std::endl;
}

void Decoration::say()
{
    std::cout << "[Decoration] some text!" << std::endl;
}

Decoration::~Decoration()
{
    std::cout << "[Decoration] deleted!" << std::endl;
}

#include "npc.h"

NPC::NPC()
{
    std::cout << "[NPC] created!" << std::endl;
}

void NPC::say()
{
    std::cout << "[NPC] some text!" << std::endl;
}

NPC::~NPC()
{
    std::cout << "[NPC] deleted!" << std::endl;
}

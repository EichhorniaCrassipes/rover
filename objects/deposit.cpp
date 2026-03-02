#include "deposit.h"

Deposit::Deposit()
{
    std::cout << "[Deposit] created!" << std::endl;
}

void Deposit::say()
{
    std::cout << "[Deposit] some text!" << std::endl;
}

Deposit::~Deposit()
{
    std::cout << "[Deposit] deleted!" << std::endl;
}

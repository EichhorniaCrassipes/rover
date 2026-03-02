#include "player.h"

Player::Player()
{
    std::cout << "[Player] created!" << std::endl;
}

void Player::say()
{
    std::cout << "[Player] some text!" << std::endl;
}

Player::~Player()
{
    std::cout << "[Player] deleted!" << std::endl;
}

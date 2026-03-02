#include "enemy.h"

Enemy::Enemy()
{
    std::cout << "[Enemy] created!" << std::endl;
}

void Enemy::say()
{
    std::cout << "[Enemy] some text!" << std::endl;
}

Enemy::~Enemy()
{
    std::cout << "[Enemy] deleted!" << std::endl;
}

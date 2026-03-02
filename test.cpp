#include <iostream>
#include <SFML/Graphics.hpp>
#include "objects/loot.h"
#include "objects/chest.h"
#include "objects/enemy.h"
#include "objects/mob.h"
#include "objects/decoration.h"
#include "objects/building.h"
#include "objects/block.h"
#include "objects/deposit.h"

using namespace std;

int main ()
{
    Loot loot;
    loot.say();

    Chest chest;
    chest.say();

    Enemy enemy;
    enemy.say();

    Mob mob;
    mob.say();

    Decoration decor;
    decor.say();

    Building building;
    building.say();

    Block block;
    block.say();

    Deposit deposit;
    deposit.say();
    return 0;
}
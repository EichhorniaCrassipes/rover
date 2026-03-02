#include <iostream>
//#include <SFML/Graphics.hpp>
#include "objects/loot.h"
#include "objects/chest.h"
#include "objects/enemy.h"
#include "objects/mob.h"
#include "objects/decoration.h"
#include "objects/building.h"
#include "objects/block.h"
#include "objects/deposit.h"
#include "objects/entity.h"
#include "objects/mapElement.h"
#include "objects/npc.h"
#include "objects/object.h"
#include "objects/player.h"

using namespace std;

int main ()
{
    Loot loot;
    loot.say();
    cout << endl;

    Chest chest;
    chest.say();
    cout << endl;

    Enemy enemy;
    enemy.say();
    cout << endl;

    Mob mob;
    mob.say();
    cout << endl;

    Decoration decor;
    decor.say();
    cout << endl;

    Building building;
    building.say();
    cout << endl;

    Block block;
    block.say();
    cout << endl;

    Deposit deposit;
    deposit.say();
    cout << endl;

    Entity entity;
    entity.say();
    cout << endl;

    MapElement mapElement;
    mapElement.say();
    cout << endl;

    NPC npc;
    npc.say();
    cout << endl;

    Object object;
    object.say();
    cout << endl;

    Player player;
    player.say();
    cout << endl;
    return 0;
}
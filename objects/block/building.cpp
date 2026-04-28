#include "building.h"


object::Building::Building(
    const string &texture_index,
    const Vector2i &position,
    const float initial_health,
    const float initial_energy_consumption,
    const float initial_wear,
    const float initial_wear_capacity
) : Block(texture_index, position)
{
    health = initial_health;
    energy_consumption = initial_energy_consumption;
    wear = initial_wear;
    wear_capacity = initial_wear_capacity;
}

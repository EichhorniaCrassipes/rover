#include "drill.h"


object::Drill::Drill(
    const string &texture_index,
    const Vector2i &position,
    const float initial_health,
    const float initial_energy_consumption,
    const float initial_wear,
    const float initial_wear_capacity,

    const float initial_mining_speed
) : Building(texture_index, position, initial_health, initial_energy_consumption, initial_wear, initial_wear_capacity)
{
    mining_speed = initial_mining_speed;
}

#include "furnace.h"


object::Furnace::Furnace(
    const string &texture_index,
    const Vector2i &position,
    const float initial_health,
    const float initial_energy_consumption,
    const float initial_wear,
    const float initial_wear_capacity,

    float initial_smelting_speed,
    float initial_burning_speed
) : Building(texture_index, position, initial_health, initial_energy_consumption, initial_wear, initial_wear_capacity)
{
    smelting_speed = initial_smelting_speed;
    burning_speed = initial_burning_speed;
}

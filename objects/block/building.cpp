#include "building.h"


object::Building::Building(
    const string &texture_index,
    const Vector2i &sprite_size,
    const Vector2i &position,
    const float initial_health
) : Block(texture_index, sprite_size, position)
{
    health = initial_health;
}


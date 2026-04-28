#include "mob.h"


object::Mob::Mob(
    const string &texture_index,
    const Vector2f &null_position,
    const float initial_health,
    const float speed
) : Entity(texture_index, null_position, speed)
{
    health = initial_health;
}

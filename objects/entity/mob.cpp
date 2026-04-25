#include "mob.h"


object::Mob::Mob(
    const string &texture_index,
    const Vector2i &sprite_size,
    const Vector2f &null_position,
    const float initial_health,
    const float speed
) : Entity(texture_index, sprite_size, null_position, speed)
{
    health = initial_health;
}

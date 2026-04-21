#include "mob.h"


object::Mob::Mob(
    const Texture* texture_link,
    const Vector2i sprite_size,
    const Vector2f &null_position,
    const float initial_health,
    const float speed
) : Entity(speed)
{
    health = initial_health;

    texture = *texture_link;
    sprite.setTextureRect({{0, 0}, sprite_size});
    position = null_position - static_cast<Vector2f>(sprite_size) / 2.f;
}

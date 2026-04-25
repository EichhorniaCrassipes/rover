#include "mob.h"

#include "../../engine/textures.h"


object::Mob::Mob(
    const string &texture_index,
    const Vector2i &sprite_size,
    const Vector2f &null_position,
    const float initial_health,
    const float speed
) : Entity(speed)
{
    health = initial_health;
    this->sprite_size = sprite_size;
    texture = game::TEXTURE_LIBRARY[texture_index];
    position = null_position - static_cast<Vector2f>(sprite_size) / 2.f;

    sprite.setTextureRect({{0, 0}, sprite_size});
}

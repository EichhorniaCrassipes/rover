#include "enemy.h"


object::Enemy::Enemy(
    const string &texture_index,
    const Vector2i &sprite_size,
    const Vector2f &null_position
) : Mob(texture_index, sprite_size, null_position) {}

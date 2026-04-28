#include "enemy.h"


object::Enemy::Enemy(
    const string &texture_index,
    const Vector2f &null_position
) : Mob(texture_index, null_position) {}

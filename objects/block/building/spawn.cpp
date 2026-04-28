#include "spawn.h"


object::Spawn::Spawn(const Vector2i &position) : Building(
    "spawn",
    position,
    1000,
    0,
    0,
    0
) {}

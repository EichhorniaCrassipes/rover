#include "stone.h"


object::Stone::Stone(
    const Vector2i &position,
    const unsigned amount,
    const float density
) : Deposit("stone deposit", position, amount, density, 1) {}

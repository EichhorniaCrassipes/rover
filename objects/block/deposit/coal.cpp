#include "coal.h"


object::Coal::Coal(
    const Vector2i &position,
    const unsigned amount,
    const float density
) : Deposit("coal deposit", position, amount, density, 1) {}

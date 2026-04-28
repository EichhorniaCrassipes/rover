#include "iron.h"


object::Iron::Iron(
    const Vector2i &position,
    const unsigned amount,
    const float density
) : Deposit("iron deposit", position, amount, density, 1.25) {}

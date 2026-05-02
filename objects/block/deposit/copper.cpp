#include "copper.h"


object::Copper::Copper(
    const Vector2i &position,
    const unsigned amount,
    const float density
) : Deposit("copper deposit", position, amount, density, 1) {}

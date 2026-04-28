#include "mk1.h"


object::FurnaceMk1::FurnaceMk1(const Vector2i &position) : Furnace(
    "furnace mk1",
    position,
    1500,
    10,
    .00333,
    2000,
    1,
    1
) {}

#include "mk1.h"


object::DrillMk1::DrillMk1(const Vector2i &position) : Drill(
    "drill mk1",
    position,
    1500,
    10,
    .00333,
    2000,
    1
) {}

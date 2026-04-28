#include "loot.h"


object::Loot::Loot(
    const string &texture_index,
    const Vector2i &position,
    const unsigned amount
) : Block(texture_index, position)
{
    this->amount = amount;
}

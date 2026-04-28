#include "deposit.h"


object::Deposit::Deposit(
    const string &texture_index,
    const Vector2i &position,
    const unsigned amount,
    const float density,
    const float mining_time
) : Block(texture_index, position) {
    this->amount = amount;
    this->density = density;
    this->mining_time = mining_time;
}

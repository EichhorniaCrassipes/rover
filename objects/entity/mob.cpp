#include "mob.h"


object::Mob::Mob(const float initial_health, const float speed) : Entity(speed) {
    health = initial_health;
}

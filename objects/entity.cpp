#include "entity.h"

object::Entity::Entity(const float speed) {
    collision = false;
    this->speed = speed;
}


float object::Entity::getSpeed() const { return speed; }
void object::Entity::setSpeed(const float new_speed) { speed = new_speed; }

void object::Entity::move(const Vector2f vector, const float delta_time) {
    if (!collision)
        position += vector * speed * delta_time;
}

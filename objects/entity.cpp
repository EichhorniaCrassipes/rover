#include "entity.h"

object::Entity::Entity() {
    collision = false;
}


void object::Entity::move(const Vector2f direction, const float speed, const float dt) {
    if (!collision)
        position += direction * speed * dt;
}

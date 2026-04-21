#include "entity.h"

object::Entity::Entity(const float speed) {
    collision = false;
    this->speed = speed;
}


float object::Entity::getSpeed() const { return speed; }
void object::Entity::setSpeed(const float new_speed) { speed = new_speed; }

void object::Entity::move(const Vector2f vector, const float delta_time) {
    if (!collision) {
        const auto delta = vector.normalized() * speed * delta_time;
        position += delta;
    }
}

bool object::Entity::checkCollision(const Object &object, const Vector2f precision_radius) {
    const auto local_bounds = getSprite().getGlobalBounds();
    const auto intersection = object.getSprite().getGlobalBounds().findIntersection({
        local_bounds.position - precision_radius,
        local_bounds.position + precision_radius,
    });

    if (intersection.has_value())
        collision = true;
    else
        collision = false;
    return collision;
}

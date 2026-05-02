#include "entity.h"

#include "../engine/libraries.h"
using sf::IntRect;

#include <iostream>
using std::cout;


object::Entity::Entity(
    const string &texture_index,
    const Vector2f &null_position,
    const float speed
) : Object(texture_index)
{
    position = null_position;// - static_cast<Vector2f>(sprite_size) / 2.f;

    collision = false;
    this->speed = speed;
}


float object::Entity::getSpeed() const { return speed; }
void object::Entity::setSpeed(const float new_speed) { speed = new_speed; }

void object::Entity::move(const Vector2f vector, const float delta_time) {
    const auto delta = vector.normalized() * speed * delta_time;

    const auto previous_position = position;
    const auto previous_collision_area = checkCollision();

    position += delta;
    const auto collision_area = checkCollision();

    position = {previous_position.x + delta.x, previous_position.y};
    const auto x_collision_area = checkCollision();

    position = {previous_position.x, previous_position.y + delta.y};
    const auto y_collision_area = checkCollision();

    if (collision_area <= previous_collision_area)
        position = previous_position + delta;
    else if (x_collision_area <= previous_collision_area)
        position = {previous_position.x + delta.x, previous_position.y};
    else if (y_collision_area <= previous_collision_area)
        position = {previous_position.x, previous_position.y + delta.y};
    else
        position = previous_position;

}

unsigned int object::Entity::checkCollision() const {
    unsigned int area = 0;
    IntRect player_hitbox = game::HITBOX_LIBRARY[getLibraryIndex()];
    player_hitbox.position += Vector2i(position);
    for (const auto object : collision_objects) {
        IntRect object_hitbox = game::HITBOX_LIBRARY[object->getLibraryIndex()];
        object_hitbox.position += Vector2i(object->getPosition());

        const auto intersection = player_hitbox.findIntersection(object_hitbox);
        if (intersection.has_value()) {
            area += intersection.value().size.x*intersection.value().size.y;
        }
    }
    return area;
}

void object::Entity::updateCollisionList(const std::vector<Object*> &objects) {
    collision_objects = objects;
}

void object::Entity::updateCollisionList(const std::vector<Entity*> &objects) {
    collision_objects.assign(objects.begin(), objects.end());
}

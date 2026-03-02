#include "entity.h"

Entity::Entity()
{
    collision = false;
}
Entity::~Entity()
= default;

void Entity::move(sf::Vector2f direction, float speed, float dt)
{
    //if no collision
    position += direction * speed * dt;
}
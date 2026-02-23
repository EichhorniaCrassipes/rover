//
// Created by arsen on 23/02/2026.
//
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
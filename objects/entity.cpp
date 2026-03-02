#include "entity.h"

Entity::Entity()
{
    collision = false;
    std::cout << "[Entity] created!" << std::endl;
}
Entity::~Entity()
{
    std::cout << "[Entity] deleted!" << std::endl;
}

void Entity::say()
{
    std::cout << "[Entity] some text!" << std::endl;
}

void Entity::move(sf::Vector2f direction, float speed, float dt)
{
    //if no collision
    position += direction * speed * dt;
}
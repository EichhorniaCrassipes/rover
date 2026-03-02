#ifndef ROVER_ENTITY_H
#define ROVER_ENTITY_H
#include "object.h"

class Entity : public Object
{
public:
    Entity();
    virtual ~Entity();
    void move(sf::Vector2f direction, float speed, float dt);
protected:
    sf::Vector2f hitbox;
    bool collision;
};
#endif //ROVER_ENTITY_H
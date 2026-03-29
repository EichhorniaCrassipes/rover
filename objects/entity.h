#ifndef ENTITY
#define ENTITY

#include "object.h"

namespace object {
    class Entity : public Object {
    public:
        Entity();
        ~Entity() override = default;

        void move(Vector2f direction, float speed, float dt);

    protected:
        Vector2f hitbox;
        bool collision;
    };
}

#endif
#ifndef ENTITY
#define ENTITY

#include "object.h"

#include <iostream>
using std::cout;


namespace object {
    class Entity : public Object {
    public:
        explicit Entity(float speed = 0);
        ~Entity() override = default;

        float getSpeed() const;
        void setSpeed(float new_speed);

        virtual void move(Vector2f vector, float delta_time);

        bool checkCollision(const Object &object, Vector2f precision_radius = {.01, .01});
    protected:
        bool collision;
        float speed;
    };
}

#endif

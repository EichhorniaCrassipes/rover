#ifndef ENTITY
#define ENTITY

#include "object.h"

namespace object {
    class Entity : public Object {
    public:
        explicit Entity(float speed = 0);
        ~Entity() override = default;

        float getSpeed() const;
        void setSpeed(float new_speed);

        virtual void move(Vector2f vector, float delta_time);
    protected:
        bool collision;
        float speed;

    };
}

#endif

#ifndef ENTITY
#define ENTITY

#include "object.h"

#include <iostream>
using std::cout;


namespace object {
    class Entity : public Object {
    public:
        explicit Entity(
            const string &texture_index,
            const Vector2i &sprite_size,
            const Vector2f &null_position,
            float speed = 0
        );
        ~Entity() override = default;

        float getSpeed() const;
        void setSpeed(float new_speed);

        virtual void move(Vector2f vector, float delta_time);

        unsigned int checkCollision(const std::vector<Entity*> &objects);
        void update(const std::vector<Entity*> &entities);
    protected:
        bool collision;
        float speed;
        std::vector<Entity*> collision_entities{};
    };
}

#endif

#ifndef ENTITY
#define ENTITY

#include "object.h"

#include <vector>
using std::vector;


namespace object {
    class Entity : public Object {
    public:
        explicit Entity(
            const string &texture_index,
            const Vector2f &null_position,
            float speed = 0
        );

        float getSpeed() const;
        void setSpeed(float new_speed);

        virtual void move(Vector2f vector, float delta_time);

        void updateCollisionList(const vector<Object*> &objects);
        void updateCollisionList(const vector<Entity*> &objects);
    protected:
        bool collision;
        float speed;

        vector<Object*> collision_objects{};
        unsigned checkCollision() const;
    };
}

#endif

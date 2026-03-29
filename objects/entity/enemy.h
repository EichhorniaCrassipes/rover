#ifndef ENEMY
#define ENEMY

#include "mob.h"

namespace object {
    class Enemy : public Mob {
    public:
        Enemy();
        ~Enemy() override = default;
    private:
        Vector2f position;
    };
}

#endif
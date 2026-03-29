#ifndef PLAYER
#define PLAYER

#include "mob.h"

namespace object {
    class Player : public Mob {
    public:
        Player();
        ~Player() override = default;
    };
}

#endif
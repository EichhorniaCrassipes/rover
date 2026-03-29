#ifndef MOB
#define MOB

#include "../entity.h"

namespace object {
    class Mob : public Entity {
    public:
        Mob();
        ~Mob() override = default;
    };
}

#endif
#ifndef MOB
#define MOB

#include "../entity.h"


namespace object {
    class Mob : public Entity {
    public:
        explicit Mob(float initial_health, float speed = 100);
    protected:
        float health;
        // another properties...
    };
}

#endif

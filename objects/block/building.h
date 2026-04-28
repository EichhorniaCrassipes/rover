#ifndef BUILDING
#define BUILDING

#include "../block.h"

namespace object {
    class Building : public Block {
    public:
        Building(
            const string &texture_index,
            const Vector2i &position,
            float initial_health
        );
    protected:
        float health;
        // another properties...
    };
}

#endif

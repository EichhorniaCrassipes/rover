#ifndef SPAWN
#define SPAWN

#include "../building.h"


namespace object {
    class Spawn : public Building {
    public:
        explicit Spawn(const Vector2i &position);
    };
}

#endif

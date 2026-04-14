#ifndef BLOCK
#define BLOCK

#include "../mapElement.h"

namespace object {
    class Block : public MapElement {
    public:
        Block() = default;
        ~Block() override = default;
    protected:
        Vector2f hitbox;
    };
}

#endif
#ifndef LOOT
#define LOOT

#include "../block.h"


namespace object {
    class Loot : public Block {
    public:
        Loot(
            const string &texture_index,
            const Vector2i &position,
            unsigned amount
        );
    protected:
        unsigned amount;
    };
}

#endif

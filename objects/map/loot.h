#ifndef LOOT
#define LOOT

#include "block.h"

namespace object {
    class Loot : public Block {
    public:
        Loot();
        ~Loot() override = default;
    };
}

#endif
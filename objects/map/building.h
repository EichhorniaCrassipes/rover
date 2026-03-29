#ifndef BUILDING
#define BUILDING

#include "block.h"

namespace object {
    class Building : public Block {
    public:
        Building();
        ~Building() override = default;
    };
}

#endif
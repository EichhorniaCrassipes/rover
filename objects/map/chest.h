#ifndef CHEST
#define CHEST

#include "building.h"

namespace object {
    class Chest : public Building {
    public:
        Chest();
        ~Chest() override = default;
    };
}

#endif
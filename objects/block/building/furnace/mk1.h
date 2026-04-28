#ifndef FURNACE_MK1
#define FURNACE_MK1

#include "../furnace.h"


namespace object {
    class FurnaceMk1 : public Furnace {
    public:
        explicit FurnaceMk1(const Vector2i &position);
    };
}

#endif

#ifndef COPPER_DEPOSIT
#define COPPER_DEPOSIT

#include "../deposit.h"


namespace object {
    class Copper : public Deposit {
    public:
        Copper(
            const Vector2i &position,
            unsigned amount,
            float density
        );
    };
}

#endif

#ifndef STONE_DEPOSIT
#define STONE_DEPOSIT

#include "../deposit.h"


namespace object {
    class Stone : public Deposit {
    public:
        Stone(
            const Vector2i &position,
            unsigned amount,
            float density
        );
    };
}

#endif

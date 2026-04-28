#ifndef IRON_DEPOSIT
#define IRON_DEPOSIT

#include "../deposit.h"


namespace object {
    class Iron : public Deposit {
    public:
        Iron(
            const Vector2i &position,
            unsigned amount,
            float density
        );
    };
}

#endif

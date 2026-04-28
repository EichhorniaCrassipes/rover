#ifndef DEPOSIT
#define DEPOSIT

#include "../block.h"

namespace object {
    class Deposit : public Block { // месторождение
    public:
        Deposit(
            const string &texture_index,
            const Vector2i &position,
            unsigned amount,
            float density,
            float mining_time
        );
    protected:
        unsigned amount;
        float density;
        float mining_time;
    };
}

#endif

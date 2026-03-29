#ifndef DEPOSIT
#define DEPOSIT

#include "block.h"

namespace object {
    class Deposit : public Block { //месторождение
    public:
        Deposit();
        ~Deposit() override = default;
    };
}

#endif
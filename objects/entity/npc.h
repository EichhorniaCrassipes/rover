#ifndef NPC_header
#define NPC_header

#include "../entity.h"

namespace object {
    class NPC : public Entity {
    public:
        NPC() = default;
        ~NPC() override = default;
    };
}

#endif
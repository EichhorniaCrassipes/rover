#ifndef BUILDING
#define BUILDING

#include "../block.h"

namespace object {
    class Building : public Block {
    public:
        Building(
            const string &texture_index,
            const Vector2i &position,
            float initial_health,
            float initial_energy_consumption,
            float initial_wear,
            float initial_wear_capacity
        );
    protected:
        float health;
        float energy_consumption;
        float wear;                 // скорость износа (каждый тик вычитается из wear_capacity)
        float wear_capacity;        // предел износа (при достижении 0 здание ломается)
    };
}

#endif

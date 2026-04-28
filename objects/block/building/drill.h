#ifndef DRILL
#define DRILL

#include "../building.h"


namespace object {
    class Drill : public Building {
    public:
        Drill(
            const string &texture_index,
            const Vector2i &position,
            float initial_health,
            float initial_energy_consumption,
            float initial_wear,
            float initial_wear_capacity,

            float initial_mining_speed
        );
    protected:
        float mining_speed;
    };
}

#endif

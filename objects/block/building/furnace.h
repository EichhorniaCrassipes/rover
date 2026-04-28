#ifndef FURNACE
#define FURNACE

#include "../building.h"


namespace object {
    class Furnace : public Building {
    public:
        Furnace(
            const string &texture_index,
            const Vector2i &position,
            float initial_health,
            float initial_energy_consumption,
            float initial_wear,
            float initial_wear_capacity,

            float initial_smelting_speed,
            float initial_burning_speed
        );
    protected:
        float smelting_speed;
        float burning_speed;    // временное решение -- скорость поглощения глобального угля (для демки)
    };                          // (нет ничего более постоянного, чем временное решение)
}

#endif

#ifndef MOB
#define MOB

#include "../entity.h"

#include <SFML/System/Vector2.hpp>
using sf::Vector2i;


namespace object {
    class Mob : public Entity {
    public:
        explicit Mob(
            const string &texture_index,
            const Vector2i &sprite_size,
            const Vector2f &null_position,
            float initial_health = 1000,
            float speed = 100
        );
    protected:
        float health;
        // another properties...
    };
}

#endif

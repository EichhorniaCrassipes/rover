#ifndef PLAYER
#define PLAYER

#include "mob.h"

#include <SFML/Graphics/View.hpp>
using sf::View;

namespace object {
    class Player : public Mob {
    public:
        explicit Player(const Vector2f &null_position = {0, 0});
        ~Player() override = default;

        void move(Vector2f vector, float delta_time);
    private:
        float speed = 250;
    };
}

#endif
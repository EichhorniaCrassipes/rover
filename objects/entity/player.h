#ifndef PLAYER
#define PLAYER

#include "mob.h"

#include <SFML/Graphics/View.hpp>
using sf::View;

namespace object {
    class Player : public Mob {
    public:
        explicit Player(const Texture* texture_link, const Vector2f &null_position = {0, 0});
        ~Player() override = default;

        void move(Vector2f vector, float delta_time);
    private:
        float speed = 250;
        sf::Vector2i spriteSize = {512,512};
    };
}

#endif
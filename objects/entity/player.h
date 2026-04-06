#ifndef PLAYER
#define PLAYER

#include "mob.h"

#include <SFML/Graphics/View.hpp>
using sf::View;

namespace object {
    class Player : public Mob {
    public:
        explicit Player(View default_view);
        ~Player() override = default;

        void zoom(float coefficient);
    private:
        View current_view;
    };
}

#endif
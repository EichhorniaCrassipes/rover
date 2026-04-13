#ifndef PLAYER
#define PLAYER

#include "mob.h"

#include <SFML/Graphics/View.hpp>
using sf::View;

namespace object {
    class Player : public Mob {
    public:
        explicit Player(const View &default_view, sf::RenderWindow *window_link);
        ~Player() override = default;

        void zoom(float coefficient);

        void move(Vector2f vector, float delta_time);
    private:
        float speed = 250;
        View current_view;
        sf::RenderWindow *window;
    };
}

#endif
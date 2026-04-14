#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics/RenderWindow.hpp>
using sf::RenderWindow;

#include <SFML/Graphics/View.hpp>
using sf::View;

using sf::Vector2f;

namespace game {
    class Camera {
    public:
        explicit Camera(RenderWindow *window_link);
        ~Camera() = default;

        void move(const Vector2f &delta);
        void zoom(float coefficient);
    private:
        RenderWindow *window;
        View current_view;
    };
}

#endif
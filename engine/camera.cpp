#include "camera.h"

#include <iostream>
using std::cout;

#include <cmath>
using std::exp;


game::Camera::Camera(RenderWindow* window_link) {
    window = window_link;
    current_view = window->getView();
}


View game::Camera::get_current_view() const {
    return current_view;
}

void game::Camera::move(const Vector2f &delta) {
    cout << "[camera/move]\n\t"
    << "delta: {" << delta.x << ';' << delta.y << "}\n\n";

    current_view.move(delta);
}

void game::Camera::zoom(const float coefficient) {
    current_view.zoom(coefficient);
}

void game::Camera::apply() const {
    window->setView(current_view);
};
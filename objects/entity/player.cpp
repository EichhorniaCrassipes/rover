#include "player.h"

#include <iostream>


object::Player::Player(const View &default_view, sf::RenderWindow *window_link) : Mob() {
    current_view = default_view;
    setScale({.04, .04});
    window = window_link;
}


void object::Player::zoom(const float coefficient) {
    current_view.zoom(coefficient);
}

void object::Player::move(const Vector2f vector, const float delta_time) {
    std::cout << "[player] moved with vector " << vector.x << " " << vector.y << std::endl;
    const Vector2f delta = vector * speed * delta_time / vector.length();
    position += delta;
    current_view.move({delta.x, -delta.y}); // возможно, надо будет домножить на текущий скейл
    window->setView(current_view);
}

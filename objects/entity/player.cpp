#include "player.h"

#include <iostream>
using std::cout;


object::Player::Player(const View &default_view, sf::RenderWindow *window_link) : Mob() {
    cout << "[player/constructor]\n\t"
    << "size: {" << sprite.getScale().x << ';' << sprite.getScale().y << "}\n\t"
    << "global bounds: {" << sprite.getGlobalBounds().size.x << ';' << sprite.getGlobalBounds().size.y << "}\n\t"
    << "position: {" << sprite.getPosition().x << ';' << sprite.getPosition().y << "}\n\n";

    current_view = default_view;
    position = current_view.getCenter() - sprite.getGlobalBounds().size / 2.f;
    setScale({.04, .04});
    window = window_link;
}


void object::Player::zoom(const float coefficient) {
    current_view.zoom(coefficient);
}

void object::Player::move(const Vector2f vector, const float delta_time) {
    cout << "[player/move]\n\t"
    << "moved with vector: {" << vector.x << ';' << vector.y << "}\n\n";

    const Vector2f delta = vector * speed * delta_time / vector.length();
    position += delta;
    current_view.move({delta.x, delta.y});
    window->setView(current_view);
}

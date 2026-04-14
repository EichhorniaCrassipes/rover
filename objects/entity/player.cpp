#include "player.h"

#include <cmath>
using std::exp;

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
    << "moved with vector: {" << vector.x << ';' << vector.y << "}\n\t";

    const auto delta = vector.normalized() * player_speed * delta_time;
    position += delta;

    move_camera(delta_time);
}

void object::Player::move_camera(const float delta_time) {
    const auto distance = position - current_view.getCenter(),
               delta = exp(-distance.length() * distance_multiplier) * camera_speed * delta_time * distance.normalized();

    cout << "camera move:\n\t\t"
    << "distance: {" << distance.x << ';' << distance.y << "}\n\t\t"
    << "delta: {" << delta.x << ';' << delta.y << "}\n\n";

    current_view.move(delta);
    window->setView(current_view);
}
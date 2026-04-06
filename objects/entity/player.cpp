#include "player.h"


object::Player::Player(View default_view) {
    current_view = default_view;
}


void object::Player::zoom(const float coefficient) {
    current_view.zoom(coefficient);
}

void object::Player::move(const Vector2f vector, const float delta_time) {
    const Vector2f delta = vector * speed * delta_time;
    position += delta;
    current_view.move(delta); // возможно, надо будет домножить на текущий скейл
}

#include "player.h"


object::Player::Player(View default_view) {
    current_view = default_view;
}


void object::Player::zoom(const float coefficient) {
    current_view.zoom(coefficient);
}

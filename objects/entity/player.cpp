#include "player.h"

#include <cmath>
using std::exp;

#include <iostream>
using std::cout;


object::Player::Player(Texture* texture_link, const Vector2f &null_position) : Mob() {
    cout << "[player/constructor]\n\t"
    << "size: {" << sprite.getScale().x << ';' << sprite.getScale().y << "}\n\t"
    << "global bounds: {" << sprite.getGlobalBounds().size.x << ';' << sprite.getGlobalBounds().size.y << "}\n\t"
    << "position: {" << sprite.getPosition().x << ';' << sprite.getPosition().y << "}\n\n";

    texture_set = texture_link;
    position = null_position - sprite.getGlobalBounds().size / 2.f;
    setScale({.04, .04});
}


void object::Player::move(const Vector2f vector, const float delta_time) {
    const auto delta = vector.normalized() * speed * delta_time;
    position += delta;
}

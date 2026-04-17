#include "player.h"

#include <cmath>
using std::exp;

#include <iostream>
using std::cout;


object::Player::Player(const Texture* texture_link, const Vector2f &null_position) : Mob() {
    cout << "[player/constructor]\n\t"
    << "size: {" << sprite.getScale().x << ';' << sprite.getScale().y << "}\n\t"
    << "global bounds: {" << sprite.getGlobalBounds().size.x << ';' << sprite.getGlobalBounds().size.y << "}\n\t"
    << "position: {" << sprite.getPosition().x << ';' << sprite.getPosition().y << "}\n\n";

    texture = *texture_link;
    sprite.setTextureRect({{0, 0}, {256, 256}});
    position = null_position - sprite.getGlobalBounds().size / 2.f;
    setScale({.5, .5});
}


void object::Player::move(const Vector2f vector, const float delta_time) {
    const auto delta = vector.normalized() * speed * delta_time;
    position += delta;

    if (vector == Vector2f{0, -1})
        sprite.setTextureRect({{0, 0}, {256, 256}});
    else if (vector == Vector2f{1, -1})
        sprite.setTextureRect({{256, 0}, {256, 256}});
    else if (vector == Vector2f{1, 0})
        sprite.setTextureRect({{512, 0}, {256, 256}});
    else if (vector == Vector2f{1, 1})
        sprite.setTextureRect({{768, 0}, {256, 256}});

    else if (vector == Vector2f{0, 1})
        sprite.setTextureRect({{1024, 0}, {256, 256}});
    else if (vector == Vector2f{-1, 1})
        sprite.setTextureRect({{1280, 0}, {256, 256}});
    else if (vector == Vector2f{-1, 0})
        sprite.setTextureRect({{1536, 0}, {256, 256}});
    else if (vector == Vector2f{-1, -1})
        sprite.setTextureRect({{1796, 0}, {256, 256}});
}

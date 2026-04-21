#include "player.h"

#include <cmath>
using std::exp;


object::Player::Player(const Texture* texture_link, const Vector2f &null_position) : Mob(1000, 250) {
    cout << "[player/constructor]\n\t"
    << "size: {" << sprite.getScale().x << ';' << sprite.getScale().y << "}\n\t"
    << "global bounds: {" << sprite.getGlobalBounds().size.x << ';' << sprite.getGlobalBounds().size.y << "}\n\t"
    << "position: {" << sprite.getPosition().x << ';' << sprite.getPosition().y << "}\n\n";

    texture = *texture_link;
    sprite.setTextureRect({{0, 0}, spriteSize});
    position = null_position - static_cast<Vector2f>(spriteSize) / 2.f;
    setScale({.5, .5});
}


void object::Player::move(const Vector2f vector, const float delta_time) {
    const auto delta = vector.normalized() * speed * delta_time;
    position += delta;

    if (vector == Vector2f{0, -1})
        sprite.setTextureRect({{0, 0}, spriteSize});
    else if (vector == Vector2f{1, -1})
        sprite.setTextureRect({{spriteSize.x, 0}, spriteSize});
    else if (vector == Vector2f{1, 0})
        sprite.setTextureRect({{spriteSize.x*2, 0}, spriteSize});
    else if (vector == Vector2f{1, 1})
        sprite.setTextureRect({{spriteSize.x*3, 0}, spriteSize});

    else if (vector == Vector2f{0, 1})
        sprite.setTextureRect({{spriteSize.x*4, 0}, spriteSize});
    else if (vector == Vector2f{-1, 1})
        sprite.setTextureRect({{spriteSize.x*5, 0}, spriteSize});
    else if (vector == Vector2f{-1, 0})
        sprite.setTextureRect({{spriteSize.x*6, 0}, spriteSize});
    else if (vector == Vector2f{-1, -1})
        sprite.setTextureRect({{spriteSize.x*7, 0}, spriteSize});
}

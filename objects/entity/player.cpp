#include "player.h"


object::Player::Player(
    const string &texture_index,
    const Vector2f &null_position
) : Mob(texture_index, {512, 512}, null_position, 1000, 250)
{
    cout << "[player/constructor]\n\t"
    << "size: {" << sprite.getScale().x << ';' << sprite.getScale().y << "}\n\t"
    << "global bounds: {" << sprite.getGlobalBounds().size.x << ';' << sprite.getGlobalBounds().size.y << "}\n\t"
    << "position: {" << sprite.getPosition().x << ';' << sprite.getPosition().y << "}\n\n";

    setScale({.5, .5});
}


void object::Player::move(const Vector2f vector, const float delta_time) {
    this->Mob::move(vector, delta_time);

    if (vector == Vector2f{0, -1})
        sprite.setTextureRect({{0, 0}, sprite_size});
    else if (vector == Vector2f{1, -1})
        sprite.setTextureRect({{sprite_size.x, 0}, sprite_size});
    else if (vector == Vector2f{1, 0})
        sprite.setTextureRect({{sprite_size.x*2, 0}, sprite_size});
    else if (vector == Vector2f{1, 1})
        sprite.setTextureRect({{sprite_size.x*3, 0}, sprite_size});

    else if (vector == Vector2f{0, 1})
        sprite.setTextureRect({{sprite_size.x*4, 0}, sprite_size});
    else if (vector == Vector2f{-1, 1})
        sprite.setTextureRect({{sprite_size.x*5, 0}, sprite_size});
    else if (vector == Vector2f{-1, 0})
        sprite.setTextureRect({{sprite_size.x*6, 0}, sprite_size});
    else if (vector == Vector2f{-1, -1})
        sprite.setTextureRect({{sprite_size.x*7, 0}, sprite_size});
}

#include "object.h"

#include "../engine/textures.h"


object::Object::Object(const string &index, const Vector2i &sprite_size) : texture(game::TEXTURE_LIBRARY[index]), sprite(texture) {
    this->sprite_size = sprite_size;
    sprite.setTextureRect({{0, 0}, sprite_size});

    scale = {.5, .5};
    position = {0, 0};
}


Sprite object::Object::getSprite() const {
    return sprite;
}
Vector2f object::Object::getPosition() const {
    return position;
}

void object::Object::setPosition(const Vector2f new_position) {
    position = new_position;
}
void object::Object::setScale(const Vector2f new_scale) {
    scale = new_scale;
}

void object::Object::render(sf::RenderWindow *window_link) {
    sprite.setPosition(position);
    sprite.setScale(scale);
    window_link->draw(sprite);
}

void object::Object::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.transform.translate(position);
    states.transform.scale(scale);
    states.texture = &texture;
    target.draw(sprite, states);
}

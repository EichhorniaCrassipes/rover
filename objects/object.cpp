#include "object.h"

object::Object::Object() : scale(Vector2f(0.5, 0.5)), position(Vector2f(0, 0)),
                   texture("textures/sample_texture.jpg"), sprite(texture) {
    sprite.setPosition(position);
    sprite.setScale(scale);
}

Sprite object::Object::getSprite() const {
    return sprite;
}

Vector2f object::Object::getPosition() const {
    return position;
}
void object::Object::setScale(Vector2f new_scale) {
    scale = new_scale;
}

void object::Object::render(sf::RenderWindow *window_link) {
    sprite.setPosition(position);
    sprite.setScale(scale);
    window_link->draw(sprite);
}
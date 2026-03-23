#include "object.h"

Object::Object() : scale(Vector2f(0.5, 0.5)), position(Vector2f(0, 0)),
                   texture("textures/sample_texture.jpg"), sprite(texture) {
    sprite.setPosition(position);
    sprite.setScale(scale);
}

Sprite Object::getSprite() const {
    return sprite;
}
#include "object.h"

Object::Object()
    : scale(sf::Vector2f(1, 1))
    , position(sf::Vector2f(0, 0))
    , texture("sample_texture.jpg")
    , sprite(texture) {
    sprite.setPosition(position);
    sprite.setScale(scale);
}
Object::~Object()
= default;
sf::Sprite Object::getSprite()
{
    return sprite;// 0 for no erros
}
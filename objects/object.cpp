#include "object.h"

Object::Object()
    : scale(sf::Vector2f(0.5, 0.5))
    , position(sf::Vector2f(0, 0))
    , texture("textures/sample_texture.jpg")
    , sprite(texture)
{
    sprite.setPosition(position);
    sprite.setScale(scale);
}
Object::~Object()
= default;
sf::Sprite Object::getSprite()
{
    return sprite;
}
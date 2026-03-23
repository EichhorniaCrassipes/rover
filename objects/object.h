#ifndef ROVER_OBJECT_H
#define ROVER_OBJECT_H
#include <SFML/Graphics.hpp>
using sf::Sprite;
using sf::Vector2f;
using sf::Texture;

class Object
{
public:
    Object();
    virtual ~Object() = default;
    Sprite getSprite() const;
protected:
    Vector2f scale;
    Vector2f position;
    Texture texture;
    Sprite sprite;
};

#endif
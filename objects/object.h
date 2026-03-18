#ifndef ROVER_OBJECT_H
#define ROVER_OBJECT_H
#include <SFML/Graphics.hpp>

class Object
{
public:
    Object();
    virtual ~Object();
    sf::Sprite getSprite();// int чтобы отлавливать ошибки, если не сделаем что-то более мудрое
protected:
    sf::Vector2f scale;
    sf::Vector2f position;
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif //ROVER_OBJECT_H
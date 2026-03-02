#pragma once
#include <SFML/Graphics.hpp>

#ifndef ROVER_OBJECT_H
#define ROVER_OBJECT_H
class Object
{
public:
    Object();
    virtual ~Object();
    virtual int draw();// int чтобы отлавливать ошибки, если не сделаем что-то более мудрое
protected:
    sf::Vector2f scale;
    sf::Vector2f position;
    //sprite_filepath
};

#endif //ROVER_OBJECT_H
#ifndef ROVER_OBJECT_H
#define ROVER_OBJECT_H

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

class Object
{
public:
    Object();
    static void say();
    virtual ~Object();
    virtual int draw();// int чтобы отлавливать ошибки, если не сделаем что-то более мудрое
protected:
    sf::Vector2f scale;
    sf::Vector2f position;
    //sprite_filepath
};

#endif //ROVER_OBJECT_H
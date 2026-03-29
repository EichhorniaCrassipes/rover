#ifndef OBJECT
#define OBJECT

#include <SFML/Graphics.hpp>
using sf::Sprite;
using sf::Vector2f;
using sf::Texture;

namespace object {
    class Object {
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
}

#endif
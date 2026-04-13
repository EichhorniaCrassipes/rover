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

        void render(sf::RenderWindow *window_link);

        Sprite getSprite() const;
        Vector2f getPosition() const;

        void setScale(Vector2f new_scale);

    protected:
        Vector2f scale;
        Vector2f position;
        Texture texture;
        Sprite sprite;
    };
}

#endif
#ifndef OBJECT
#define OBJECT

#include <SFML/Graphics.hpp>
using sf::Sprite;
using sf::Vector2f;
using sf::Texture;

#include <SFML/System/Vector2.hpp>
using sf::Vector2i;

#include <map>
using std::map;

#include <string>
using std::string;


namespace object {
    class Object : public sf::Drawable, public sf::Transformable {
    public:
        explicit Object(const string &index = "default", const Vector2i &sprite_size = {0, 0});

        void render(sf::RenderWindow *window_link);

        Sprite getSprite() const;
        Vector2f getPosition() const;

        void setPosition(Vector2f new_position);
        void setScale(Vector2f new_scale);
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    protected:
        Vector2f scale;
        Vector2f position;

        Vector2i sprite_size;

        Texture texture;
        Sprite sprite;
    };
}

#endif

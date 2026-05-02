#ifndef OBJECT
#define OBJECT

#include <SFML/Graphics/Drawable.hpp>
using sf::Drawable;
using sf::RenderTarget;
using sf::RenderStates;

#include <SFML/Graphics/Transformable.hpp>
using sf::Transformable;

#include <SFML/Graphics/Texture.hpp>
using sf::Texture;

#include <SFML/Graphics/Sprite.hpp>
using sf::Sprite;

#include <SFML/System/Vector2.hpp>
using sf::Vector2f;
using sf::Vector2i;

#include <map>
using std::map;

#include <string>
using std::string;


namespace object {
    class Object : public Drawable, public Transformable {
    public:
        explicit Object(const string &index = "default");

        Sprite getSprite() const;
        Vector2f getPosition() const;
        string getLibraryIndex() const;
        Vector2f getScale() const;

        void setPosition(Vector2f new_position);
        void setScale(Vector2f new_scale);
        void draw(RenderTarget &target, RenderStates states) const override;
        string index;
    protected:
        Vector2f scale;
        Vector2f position;
        Vector2i sprite_size;

        Texture texture;
        Sprite sprite;
    };
}

#endif

#ifndef ROVER_GHOST_H
#define ROVER_GHOST_H
#include "../object.h"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Transformable.hpp"

class Ghost : public object::Object
{
    public:
    Ghost(const string& texture, sf::Vector2f scale, const string& shader);
    void draw(RenderTarget &target, RenderStates states) const override;
private:
    const string& index;
};

#endif //ROVER_GHOST_H
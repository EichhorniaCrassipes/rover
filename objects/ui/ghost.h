#ifndef ROVER_GHOST_H
#define ROVER_GHOST_H
#include <vector>

#include "../object.h"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Transformable.hpp"

class Ghost : public object::Object
{
    public:
    Ghost(const string& texture, sf::Vector2f scale);
    void draw(RenderTarget &target, RenderStates states) const override;
    bool checkCollision() const;

    void updateCollisionList(const std::vector<Object *> &objects);
    void updateShader(const string& shader);
private:
    string index;
    std::vector<Object*> collision_objects{};
};

#endif //ROVER_GHOST_H
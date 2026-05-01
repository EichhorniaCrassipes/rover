#include "ghost.h"

#include <iostream>

#include "SFML/Graphics/RenderTarget.hpp"
#include "../../engine/libraries.h"
#include "SFML/Window/Mouse.hpp"

Ghost::Ghost(const string& texture, const sf::Vector2f scale)
    :Object(texture)
{
    this->index = texture;
    setScale(scale);
}

void Ghost::draw(RenderTarget &target, RenderStates states) const {
    states.transform *= getTransform();
    states.transform.translate(position);
    states.transform.translate({ - static_cast<float>(sprite.getTexture().getSize().x)/2, - static_cast<float>(sprite.getTexture().getSize().y)/2});
    states.texture = &texture;
    if (game::SHADER_LIBRARY.count(shader_index))
        states.shader = &game::SHADER_LIBRARY.at(shader_index);
    target.draw(sprite, states);
    //std::cout << "shader: " << states.shader << std::endl;

}

bool Ghost::checkCollision() const {
    bool collision = false;
    IntRect player_hitbox = game::HITBOX_LIBRARY[getLibraryIndex()];
    //std::cout << getLibraryIndex() << std::endl;
    //std::cout << player_hitbox.position.x << std::endl;
    //std::cout << player_hitbox.position.x << std::endl;
    for (const auto object : collision_objects) {
        IntRect object_hitbox = game::HITBOX_LIBRARY[object->getLibraryIndex()];

        const auto intersection = player_hitbox.findIntersection(object_hitbox);
        if (intersection.has_value()) {
            collision = true;
        }
    }
    return collision;
}

void Ghost::updateCollisionList(const std::vector<Object*> &objects) {
    collision_objects = objects;
}
void Ghost::updateShader(const string &shader) {
    shader_index = shader;
}
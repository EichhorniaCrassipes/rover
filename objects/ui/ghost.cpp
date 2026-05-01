#include "ghost.h"

#include <iostream>

#include "SFML/Graphics/RenderTarget.hpp"
#include "../../engine/libraries.h"
#include "SFML/Window/Mouse.hpp"

Ghost::Ghost(const string& texture, const sf::Vector2f scale, const string& shader)
    :Object(texture), index(shader)
{
    setScale(scale);
}

void Ghost::draw(RenderTarget &target, RenderStates states) const {
    states.transform *= getTransform();
    states.transform.translate(position);
    states.transform.translate({ - static_cast<float>(sprite.getTexture().getSize().x)/2, - static_cast<float>(sprite.getTexture().getSize().y)/2});
    states.texture = &texture;
    if (game::SHADER_LIBRARY.count("green"))
        states.shader = &game::SHADER_LIBRARY.at("green");
    target.draw(sprite, states);
    //std::cout << "shader: " << states.shader << std::endl;

}
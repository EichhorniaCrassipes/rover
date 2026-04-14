#include "stone.h"


Stone::Stone(sf::Vector2f pos,string biome, char variation = 0)
{
    position = pos;
    scale = sf::Vector2f(1,1);
    if (biome == "test0")
        texture = sf::Texture("textures/stone.png", false, sf::IntRect({0, variation * 64}, {64, 64}));
    if (biome == "test1")
        texture = sf::Texture("textures/stone.png", false, sf::IntRect({64, variation * 64}, {64, 64}));
    sprite = sf::Sprite(texture);
    sprite.setPosition(position);
    sprite.setScale({1,1});
}
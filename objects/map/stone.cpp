#include "stone.h"


Stone::Stone(sf::Vector2f pos,string biome, char variation = 0)
{
    position = pos;
    if (biome == "test0")
        texture = sf::Texture("textures/stone.png", false, sf::IntRect({0, variation * 64}, {64, 64}));
    if (biome == "test1")
        texture = sf::Texture("textures/stone.png", false, sf::IntRect({64, variation * 64}, {64, 64}));
    sprite = sf::Sprite(texture);
}
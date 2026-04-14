#include "stone.h"


Stone::Stone(string biome, char variation = 0)
{
    if (biome == "test0")
        texture = sf::Texture("textures/stone.png", false, sf::IntRect({0, variation * 64}, {64, 64}));
    if (biome == "test0")
        texture = sf::Texture("textures/stone.png", false, sf::IntRect({64, variation * 64}, {64, 64}));
}
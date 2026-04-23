#include "stone.h"


object::Stone::Stone(const Vector2f pos, const string &biome, const unsigned char variation) {
    position = {pos.x*64,pos.y*64};
    scale = Vector2f(1,1);
    if (biome == "test0")
        texture = Texture("textures/stone.png", false, sf::IntRect({0, variation * 64}, {64, 64}));
    if (biome == "test1")
        texture = Texture("textures/stone.png", false, sf::IntRect({64, variation * 64}, {64, 64}));
    if (biome == "test2")
        texture = Texture("textures/stone.png", false, sf::IntRect({128, variation * 64}, {64, 64}));
    sprite = Sprite(texture);
    sprite.setPosition(position);
    sprite.setScale({1,1});
}

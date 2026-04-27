#ifndef LIBRARIES
#define LIBRARIES

#include <map>
using std::map;

#include <string>
using std::string;

#include <SFML/Graphics/Texture.hpp>
using sf::Texture;

#include "SFML/Graphics/Rect.hpp"
using sf::IntRect;


namespace game {
    inline map<string, Texture> TEXTURE_LIBRARY = {
        {"tileset", Texture("textures/test01.png")},
        {"decoset", Texture("textures/deco01.png")},
        {"default", Texture("textures/sample_texture.jpg")},
        {"player",  Texture("textures/player.png")},
        {"spawn",  Texture("textures/antenna.png")},
        {"stone deposit",  Texture("textures/stone_deposit.png")},
        {"iron deposit",  Texture("textures/iron_deposit.png")},
        {"copper deposit",  Texture("textures/copper_deposit.png")},
        {"coal deposit",  Texture("textures/coal_deposit.png")},
        {"furnace",  Texture("textures/furnace.png")}
    };

    inline map<string, IntRect> HITBOX_LIBRARY = {
        /* thePosition: координаты верхней левой точки хитбокса по
         *              спрайту в дефолтной системе координат экрана
         * theSize: размер хитбокса
         */
        {"player", {{8, 50}, {238, 160}}},
        {"spawn", {{11, 21}, {117, 200}}},
        {"furnace", {{0, 0}, {256, 256}}},
    };
}

#endif

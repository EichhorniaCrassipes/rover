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
        {"spawn",  Texture("textures/antenna.png")}
    };

    inline map<string, Vector2i> TEXTURE_SIZE_LIBRARY = {
        {"default", {128, 128}},
        {"player", {512, 512}},
        {"spawn", {128, 256}}
    };

    inline map<string, IntRect> HITBOX_LIBRARY = {
        /* thePosition: координаты верхней левой точки хитбокса по
         *              спрайту в дефолтной системе координат экрана
         * theSize: размер хитбокса
         */
        {"player", {{8, 50}, {238, 160}}},
        {"spawn", {{11, 21}, {117, 200}}}
    };
}

#endif

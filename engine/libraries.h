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

#include <SFML/Graphics/Shader.hpp>
using sf::Shader;


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
        {"furnace",  Texture("textures/furnace.png")},
        {"drill",  Texture("textures/drill.png")}
    };

    inline map<string, Vector2i> TEXTURE_SIZE_LIBRARY = {
        {"default", {128, 128}},
        {"player", {512, 512}},
        {"spawn", {128, 256}},
        {"drill", {192,192}},
        {"stone deposit", {64, 64}},
        {"iron deposit", {64, 64}},
        {"copper deposit", {64, 64}},
        {"coal deposit", {64, 64}}
    };

    inline map<string, IntRect> HITBOX_LIBRARY = {
        /* thePosition: координаты верхней левой точки хитбокса по
         *              спрайту в дефолтной системе координат экрана
         * theSize: размер хитбокса
         */
        {"player", {{8, 50}, {238, 160}}},
        {"spawn", {{11, 21}, {117, 200}}},
        {"furnace", {{0, 0}, {128, 128}}},
        {"drill", {{0, 0}, {192, 192}}},
    };

    inline map<string, Shader> SHADER_LIBRARY;
}

#endif

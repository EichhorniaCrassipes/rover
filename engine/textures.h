#ifndef TEXTURE_LIBRARY_h
#define TEXTURE_LIBRARY_h

#include <map>
using std::map;

#include <string>
using std::string;

#include "SFML/Graphics/Texture.hpp"
using sf::Texture;


namespace game {
    inline map<string, Texture> TEXTURE_LIBRARY = {
        {"tileset", Texture("textures/test01.png")},
        {"decoset", Texture("textures/deco01.png")},
        {"default", Texture("textures/sample_texture.jpg")},
        {"player",  Texture("textures/player.png")}
    };
}

#endif

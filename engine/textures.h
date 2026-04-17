#ifndef TEXTURES
#define TEXTURES

#include <map>
#include <string>

#include "SFML/Graphics/Texture.hpp"
using std::string;
using std::map;
using sf::Texture;

namespace game {
    extern map<string, Texture*> textures;


}

#endif
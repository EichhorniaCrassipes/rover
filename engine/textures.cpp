#include "textures.h"

map <string, Texture*> game::textures = {
    {"textures/test01.png", new Texture},
    {"textures/deco01.png", new Texture},
    {"textures/sample_texture.jpg", new Texture},
    {"textures/player.png", new Texture}
};

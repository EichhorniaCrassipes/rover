#ifndef ROVER_TESTSCENE_H
#define ROVER_TESTSCENE_H

#include "UIScene.h"

#include <SFML/Graphics/RenderWindow.hpp>
using sf::RenderWindow;

namespace scene {
    class TestScene : public UIScene {
    public:
        explicit TestScene(RenderWindow* window_link, unsigned short* scene_index_link);
    };
}

#endif
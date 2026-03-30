#ifndef ROVER_ENGINE_H
#define ROVER_ENGINE_H

#include "../scenes/game/gameScene.h"
#include "../scenes/UI/UIScene.h"

#include "enums.h"

#include <SFML/Graphics/RenderWindow.hpp>
using sf::RenderWindow;
using sf::Clock;

#include <string>
using std::string;


namespace game {
    class Engine {
    public:
        Engine();
        explicit Engine(const string &name);
        Engine(unsigned short width, unsigned short height);
        Engine(unsigned short width, unsigned short height, const string &name);
        ~Engine();

        void run(short fps = 0) const;
    private:
        RenderWindow* window;
        scene::GameScene** game_scenes;
        scene::UIScene** UI_scenes;
        Clock* timer;

        static unsigned short scene_index;

        void loop() const;
    };
}

#endif
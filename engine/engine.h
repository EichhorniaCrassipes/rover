#ifndef ROVER_ENGINE_H
#define ROVER_ENGINE_H

#include "../scenes/scene.h"

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
        Scene** scenes;
        Clock* timer;

        short scene_index = 0;

        void loop() const;
    };
}

#endif
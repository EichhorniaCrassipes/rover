#ifndef ROVER_UI_SCENE_H
#define ROVER_UI_SCENE_H

#include <SFML/Window/Event.hpp>
using sf::Event;

#include <vector>
using std::vector;

#include <map>
using std::map;

namespace scene {
    class UIScene {
    public:
        UIScene() = default;
        virtual ~UIScene() = default;

        void render();
        void update();
        bool event(const Event &event); // возвращает true, если произошла какая-либо обработка
    private:
        // std::map<int, map<int, UIObject>> objects;
        // media (OST + ...)
    };
}

#endif
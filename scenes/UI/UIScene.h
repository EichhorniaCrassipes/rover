#ifndef ROVER_UI_SCENE_H
#define ROVER_UI_SCENE_H

#include <SFML/Window/Event.hpp>
using sf::Event;

#include <SFML/Graphics/RenderWindow.hpp>
using sf::RenderWindow;

#include <vector>
using std::vector;

#include <map>
using std::map;

#include "../../engine/stats.h"
using game::EngineStats;

#include "../../objects/object.h"

namespace scene {
    class UIScene {
    public:
        explicit UIScene(RenderWindow* window_link, EngineStats* scene_index_link);
        virtual ~UIScene();

        void render() const;
        void update();
        bool event(const Event &event); // возвращает true, если произошла какая-либо обработка
    protected:
        RenderWindow* window;
        EngineStats* scene_index;

        vector<object::Object*> test_pull;
        // std::map<int, map<int, UIObject>> objects;
        // media (OST + ...)
    };
}

#endif
#ifndef ROVER_GAME_SCENE_H
#define ROVER_GAME_SCENE_H

#include <SFML/Window/Event.hpp>
using sf::Event;

#include <SFML/Graphics/RenderWindow.hpp>
using sf::RenderWindow;

#include <SFML/System/Clock.hpp>
using sf::Clock;

#include <vector>
using std::vector;

#include <map>
using std::map;

#include "../../engine/stats.h"
using game::EngineStats;

#include "../../objects/map/block.h"
#include "../../objects/entity.h"

namespace scene {
    class GameScene {
    public:
        explicit GameScene(RenderWindow* window_link, EngineStats* scene_index_link);
        virtual ~GameScene() = default;

        void render();
        void update();
        bool event(const Event &event); // возвращает true, если произошла какая-либо обработка
    protected:
        RenderWindow* window;
        EngineStats* scene_index;

        Clock FPS_timer;
        double delta_time;

        map<int, map<int, object::Block>> upper_decorations, interactive_blocks;
        vector<object::Entity> entities;
        // tilemap нижних декораций
        // tilemap карты
    };
}

#endif
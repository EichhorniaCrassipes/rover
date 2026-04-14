#ifndef ROVER_GAME_SCENE_H
#define ROVER_GAME_SCENE_H

#include <SFML/Window/Event.hpp>

#include "../../generator/mapGenerator.h"
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
#include "../../objects/entity/player.h"

namespace scene {
    class GameScene {
    public:
        explicit GameScene(RenderWindow* window_link, EngineStats* engine_stats_link);
        virtual ~GameScene() = default;

        void render();
        void update();
        bool event(const Event &event); // возвращает true, если произошла какая-либо обработка

        void reseed(long long generator_seed);
    protected:
        RenderWindow* window;
        EngineStats* engine_stats_link;

        Clock FPS_timer;
        float delta_time;

        map<int, map<int, object::Block>> upper_decorations, interactive_blocks;
        vector<object::Entity> entities;

        vector<sf::Drawable*> active_chunks;
        generator::MapGenerator generator;

        object::Player player;
    private:
        void handle_player();
    };
}

#endif
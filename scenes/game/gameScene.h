#ifndef ROVER_GAME_SCENE_H
#define ROVER_GAME_SCENE_H

#include <deque>
#include <SFML/Window/Event.hpp>

namespace generator {
    class ChunkDecorations;
    class Chunk;
}

using sf::Event;

#include <SFML/Graphics/RenderWindow.hpp>
using sf::RenderWindow;

#include <SFML/Graphics/Drawable.hpp>
using sf::Drawable;

#include <SFML/System/Clock.hpp>
using sf::Clock;

#include <vector>
using std::vector;

#include <map>
using std::map;

#include "../../generator/mapGenerator.h"
using generator::MapGenerator;

#include "../../engine/stats.h"
using game::EngineStats;

#include "../../engine/camera.h"
using game::Camera;

#include "../../objects/map/block.h"
#include "../../objects/entity.h"
#include "../../objects/entity/player.h"

namespace scene {
    class GameScene {
    public:
        explicit GameScene(RenderWindow* window_link, Camera* camera_link, EngineStats* engine_stats_link);
        virtual ~GameScene();

        void render();
        void update();
        bool event(const Event &event); // возвращает true, если произошла какая-либо обработка

        void reseed(long long generator_seed);
    protected:
        RenderWindow* window;
        EngineStats* engine_stats;
        Camera* camera;

        Clock FPS_timer;
        float delta_time;

        map<int, map<int, object::Block>> upper_decorations, interactive_blocks;
        vector<object::Entity> entities;

        std::deque<generator::Chunk*> active_chunks;
        std::deque<generator::ChunkDecorations*> active_decoration_chunks;
        vector<object::Block*> blocks;
        MapGenerator generator;

        object::Player player;
    private:
        void handle_player(const Vector2f &move_vector);
        void handle_camera(const Vector2f &move_vector);

        static Vector2f get_move_vector();

        float camera_speed = 200,
              distance_multiplier = 0.0001,
              distance_threshold = 1.5,
              move_vector_multiplier = 30,
              zoom_coefficient = 0.05,
              render_distance = 1;
    };
}

#endif
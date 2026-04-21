#ifndef ROVER_GAME_SCENE_H
#define ROVER_GAME_SCENE_H

#include "../scene.h"
using sf::Drawable;

#include <SFML/System/Clock.hpp>
using sf::Clock;

#include <vector>
using std::vector;

#include <map>
using std::map;

#include "../../generator/mapGenerator.h"
using generator::MapGenerator;

#include "../../engine/camera.h"
using game::Camera;

#include "../../generator/chunk.h"
#include "../../generator/chunkDecorations.h"

#include "../../objects/map/block.h"
#include "../../objects/entity.h"
#include "../../objects/entity/player.h"

namespace scene {
    class GameScene : public Scene {
    public:
        explicit GameScene(RenderWindow* window_link, Camera* camera_link, EngineStats* engine_stats_link, map<string, Texture*>* textures);
        ~GameScene() override;

        void render() override;
        void update() override;
        Status event(const Event &event) override;

        void on_start() override;
        void on_end() override;

        void reseed(long long generator_seed);
    protected:
        Camera* camera;

        Clock FPS_timer;
        float delta_time;

        map<int, map<int, object::Block>> upper_decorations, interactive_blocks;
        vector<object::Entity> entities;

        std::vector<generator::Chunk*> active_chunks;
        std::vector<generator::ChunkDecorations*> active_decoration_chunks;
        //vector<object::Block*> blocks;
        MapGenerator generator;

        object::Player player;
    private:
        void handle_player(const Vector2f &move_vector);
        void handle_camera(const Vector2f &move_vector);
        void update_chunks();

        static Vector2f get_move_vector();

        float camera_speed = 200,
              distance_multiplier = 0.0001,
              distance_threshold = 1.5,
              move_vector_multiplier = 30,
              zoom_coefficient = 0.05,
              render_distance = 10,
              render_distance_squared = render_distance * render_distance;
        map<string, Texture*>* scene_textures;
    };
}

#endif

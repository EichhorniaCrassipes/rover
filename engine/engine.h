#ifndef ROVER_ENGINE_H
#define ROVER_ENGINE_H

#include "../scenes/game/gameScene.h"
#include "../scenes/UI/UIScene.h"

#include <SFML/Graphics/RenderWindow.hpp>
using sf::RenderWindow;

#include <SFML/System/Clock.hpp>
using sf::Clock;
using sf::Time;

#include <SFML/Graphics/Font.hpp>
using sf::Font;

#include <SFML/Graphics/Text.hpp>
using sf::Text;

#include <string>
using std::string;

#include <array>
using std::array;


namespace game {
    class Engine {
    public:
        Engine();
        explicit Engine(const string &name);
        ~Engine();

        void run(short fps = 0);
    private:
        RenderWindow* window;
        Camera** cameras;

        scene::GameScene** game_scenes;
        scene::UIScene** UI_scenes;

        Clock TPS_timer, count_display_timer;
        Time last_tps_time_value;

        Font default_monospace_font;
        Text *FPS, *FPS_delta, *TPS, *TPS_delta;
        unsigned short frames, last_fps_update_value,
                       ticks, last_tps_update_value;

        Text *mouse_position, *scene_num, *version;
        array<Text*, 7> info_texts{};

        Text exitDialog_text;

        float current_real_TPS;
        Clock TPS_adjuster_timer;

        void loop();

        inline void render(scene::GameScene* game, scene::UIScene* ui, const Camera* camera);
        inline void update(scene::GameScene* game, scene::UIScene* ui);

        void info_update_values();
        void info_overdraw() const;

        void adjust_tps();
        bool adjustment_proceeding = false;
        float left_target = 0, right_target = 0;
    };
}

#endif
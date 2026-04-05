#ifndef ROVER_ENGINE_H
#define ROVER_ENGINE_H

#include "../scenes/game/gameScene.h"
#include "../scenes/UI/UIScene.h"

#include <SFML/Graphics/RenderWindow.hpp>
using sf::RenderWindow;
using sf::Clock;
using sf::Time;

using sf::Font;
using sf::Text;

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

        void run(short fps = 0);
    private:
        RenderWindow* window;

        scene::GameScene** game_scenes;
        scene::UIScene** UI_scenes;

        Clock TPS_timer, count_display_timer;
        Time last_tps_time_value;

        Font default_monospace_font;
        Text FPS, FPS_delta, TPS, TPS_delta;
        unsigned short frames, last_fps_update_value,
                       ticks, last_tps_update_value;

        Text mouse_position, scene_num, version;

        void loop();

        void info_overdraw();
    };
}

#endif
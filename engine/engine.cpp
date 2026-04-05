#include "engine.h"
using sf::VideoMode;
using sf::Clock;
using sf::Event;

#include <iostream>
using std::cerr;

#include "enums.h"
EngineStats game::global_stats {scenes::LOADING, 0, 0};

#include "../scenes/UI/testScene.h"


game::Engine::Engine() : Engine(DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_TITLE) {}
game::Engine::Engine(const string &name) : Engine(DEFAULT_WIDTH, DEFAULT_HEIGHT, name) {}
game::Engine::Engine(const unsigned short width, const unsigned short height) : Engine(width, height, DEFAULT_TITLE) {}
game::Engine::Engine(const unsigned short width, const unsigned short height, const string &name) {
    window = new RenderWindow(
        VideoMode({width, height}),
        name
    );
    game_scenes = new scene::GameScene*[scenes::CAP];
    UI_scenes = new scene::UIScene*[scenes::CAP];
    timer = new Clock();
}

game::Engine::~Engine() {
    for (unsigned short i = 0; i < scenes::CAP; i++) {
        delete game_scenes[i];
        delete UI_scenes[i];
    }
    delete[] game_scenes;
    delete[] UI_scenes;

    delete timer;
    delete window;
}

void game::Engine::run(const short fps) const {
    game_scenes[scenes::LOADING]   = nullptr;
    game_scenes[scenes::MAIN_MENU] = new scene::GameScene(window, &global_stats);
    game_scenes[scenes::CUTSCENE]  = nullptr;
    game_scenes[scenes::MAIN_GAME] = new scene::GameScene(window, &global_stats);

    UI_scenes[scenes::LOADING]   = new scene::UIScene(window, &global_stats);
    UI_scenes[scenes::MAIN_MENU] = new scene::UIScene(window, &global_stats);
    UI_scenes[scenes::CUTSCENE]  = new scene::TestScene(window, &global_stats);
    UI_scenes[scenes::MAIN_GAME] = new scene::UIScene(window, &global_stats);

    if (fps > 0) window->setFramerateLimit(fps);
    else window->setVerticalSyncEnabled(true);

    timer->restart();
    loop();
}

void game::Engine::loop() const {
    while (window->isOpen()) {
        window->clear();
        const auto current_UI_scene = UI_scenes[global_stats.current_scene_index];
        const auto current_game_scene = game_scenes[global_stats.current_scene_index];

        while (const auto event = window->pollEvent()) {
            if (event->is<Event::Closed>())
                window->close();

            try {
                bool UI_event_update = false;
                if (current_UI_scene != nullptr)
                    UI_event_update = current_UI_scene->event(*event);
                if (!UI_event_update && current_game_scene != nullptr)
                    current_game_scene->event(*event);
            }
            catch (const std::runtime_error &e) {
                cerr << e.what() << '\n';
            }
        }

        if (current_game_scene != nullptr)
            current_game_scene->render();
        if (current_UI_scene != nullptr)
            current_UI_scene->render();

        window->display();
        if (timer->getElapsedTime() >= UPS_delta) {
            timer->restart();
            if (current_UI_scene != nullptr)
                current_UI_scene->update();
            if (current_game_scene != nullptr)
                current_game_scene->update();
        }
    }
}

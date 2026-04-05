#include "engine.h"
using sf::VideoMode;
using sf::Clock;
using sf::Event;

#include <iostream>
using std::cerr;

#include "enums.h"

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

    scene_index = scenes::CUTSCENE;
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
    game_scenes[scenes::LOADING]   = new scene::GameScene(window, &scene_index);
    game_scenes[scenes::MAIN_MENU] = new scene::GameScene(window, &scene_index);
    game_scenes[scenes::CUTSCENE]  = new scene::GameScene(window, &scene_index);
    game_scenes[scenes::MAIN_GAME] = new scene::GameScene(window, &scene_index);

    UI_scenes[scenes::LOADING]   = new scene::UIScene(window, &scene_index);
    UI_scenes[scenes::MAIN_MENU] = new scene::UIScene(window, &scene_index);
    UI_scenes[scenes::CUTSCENE]  = new scene::TestScene(window, &scene_index);
    UI_scenes[scenes::MAIN_GAME] = new scene::UIScene(window, &scene_index);

    if (fps > 0) window->setFramerateLimit(fps);
    else window->setVerticalSyncEnabled(true);

    timer->restart();
    loop();
}

void game::Engine::loop() const {
    while (window->isOpen()) {
        window->clear();

        while (const auto event = window->pollEvent()) {
            if (event->is<Event::Closed>())
                window->close();

            try {
                UI_scenes[scene_index]->event(*event);
                game_scenes[scene_index]->event(*event);
            }
            catch (const std::runtime_error &e) {
                cerr << e.what() << '\n';
            }
        }

        game_scenes[scene_index]->render();
        UI_scenes[scene_index]->render();

        window->display();
        if (timer->getElapsedTime() >= UPS_delta) {
            timer->restart();
            UI_scenes[scene_index]->update();
            game_scenes[scene_index]->update();
        }
    }
}

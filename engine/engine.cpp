#include "engine.h"
using sf::VideoMode;
using sf::Clock;
using sf::Event;

#include <iostream>
using std::cerr;

#include "enums.h"


game::Engine::Engine() : Engine(DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_TITLE) {}
game::Engine::Engine(const string &name) : Engine(DEFAULT_WIDTH, DEFAULT_HEIGHT, name) {}
game::Engine::Engine(const unsigned short width, const unsigned short height) : Engine(width, height, DEFAULT_TITLE) {}
game::Engine::Engine(const unsigned short width, const unsigned short height, const string &name) {
    window = new RenderWindow(
        VideoMode({width, height}),
        name
    );
    scenes = new Scene*[SCENES_CAP];
    timer = new Clock();
}

game::Engine::~Engine() {
    for (unsigned short i = 0; i < SCENES_CAP; i++) delete scenes[i];
    delete[] scenes;

    delete timer;
    delete window;
}

void game::Engine::run(const short fps) const {
    scenes[0] = new Scene();
    scenes[1] = new Scene();
    scenes[2] = new Scene();
    scenes[3] = new Scene();

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
                scenes[scene_index]->event(*event);
            }
            catch (const std::runtime_error &e) {
                cerr << e.what() << '\n';
            }
        }

        scenes[scene_index]->render();

        window->display();
        if (timer->getElapsedTime() >= UPS_delta) {
            timer->restart();
            scenes[scene_index]->update();
        }
    }
}

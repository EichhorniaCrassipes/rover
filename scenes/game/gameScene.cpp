#include "gameScene.h"

#include <SFML/Window/Keyboard.hpp>


scene::GameScene::GameScene(RenderWindow* window_link, EngineStats* scene_index_link) : player(window_link->getDefaultView()) {
    window      = window_link;
    scene_index = scene_index_link;
    FPS_timer.start();
    delta_time = 0;
}


void scene::GameScene::render() {
    delta_time = FPS_timer.getElapsedTime().asSeconds();
    FPS_timer.restart();
}

void scene::GameScene::update() {}

bool scene::GameScene::event(const Event &event) {
    bool updated = false;
    if (const auto key = event.getIf<Event::KeyPressed>())
        switch (key->code) {
            case sf::Keyboard::Key::W:
            case sf::Keyboard::Key::Up:
                player.move({0, 1}, delta_time);
                updated = true;
                break;
            case sf::Keyboard::Key::A:
            case sf::Keyboard::Key::Left:
                player.move({-1, 0}, delta_time);
                updated = true;
                break;
            case sf::Keyboard::Key::S:
            case sf::Keyboard::Key::Down:
                player.move({0, -1}, delta_time);
                updated = true;
                break;
            case sf::Keyboard::Key::D:
            case sf::Keyboard::Key::Right:
                player.move({1, 0}, delta_time);
                updated = true;
                break;
            default: break;
        }
    return updated;
}

#include "gameScene.h"

#include <SFML/Window/Keyboard.hpp>

#include "../../objects/map/chunk.h"

scene::GameScene::GameScene(RenderWindow* window_link, EngineStats* scene_index_link) : gen(0, 1),
                                                                                        player(window_link->getDefaultView()) {
    window      = window_link;
    scene_index = scene_index_link;
    FPS_timer.start();
    delta_time = 0;
    test_pull.push_back(new Chunk(generator::MapGenerator(0, 1), 0, 0));
    test_pull.push_back(new Chunk(generator::MapGenerator(0, 1), 16, 0));
    test_pull.push_back(new Chunk(generator::MapGenerator(0, 1), 0, 16));
    test_pull.push_back(new Chunk(generator::MapGenerator(0, 1), 16, 16));
}


void scene::GameScene::render() {
    delta_time = FPS_timer.getElapsedTime().asSeconds();
    FPS_timer.restart();
    for (const auto o : test_pull)
        window->draw(*o);
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

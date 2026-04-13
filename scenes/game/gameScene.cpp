#include "gameScene.h"

#include <iostream>
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
    player.render(window);

    float x = 0, y = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        y = 1;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        y = -1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        x = 1;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        x = -1;

    if (x != 0 || y != 0)
        player.move({x, y}, delta_time);
}

void scene::GameScene::update() {}

bool scene::GameScene::event(const Event &event) {
    bool updated = false;

    return updated;
}

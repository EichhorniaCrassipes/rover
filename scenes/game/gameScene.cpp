#include "gameScene.h"

#include <iostream>
#include <SFML/Window/Keyboard.hpp>

#include "../../objects/map/chunk.h"

scene::GameScene::GameScene(RenderWindow* window_link, EngineStats* engine_stats_link) : generator(0, 1),
                                                                                         player(window_link->getDefaultView(), window_link) {
    window                  = window_link;
    this->engine_stats_link = engine_stats_link;
    delta_time              = 0;
    FPS_timer.start();
    active_chunks.push_back(new Chunk(generator, 0, 0));
    active_chunks.push_back(new Chunk(generator, 16, 0));
    active_chunks.push_back(new Chunk(generator, 0, 16));
    active_chunks.push_back(new Chunk(generator, 16, 16));
}


void scene::GameScene::render() {
    delta_time = FPS_timer.getElapsedTime().asSeconds();
    FPS_timer.restart();
    for (const auto chunk : active_chunks)
        window->draw(*chunk);

    handle_player();
}

void scene::GameScene::handle_player() {
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
    player.render(window);
}

void scene::GameScene::update() {}

bool scene::GameScene::event(const Event &event) {
    bool updated = false;

    return updated;
}

void scene::GameScene::reseed(const long long generator_seed) {
    generator.reseed(generator_seed);
}

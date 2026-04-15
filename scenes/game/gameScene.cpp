#include "gameScene.h"

#include <iostream>
using std::cout;

#include <cmath>
using std::exp;

#include <SFML/Window/Keyboard.hpp>

#include "../../objects/map/chunk.h"

scene::GameScene::GameScene(RenderWindow* window_link, Camera* camera_link, EngineStats* engine_stats_link) : generator(0, 1),
                                                                                                              player(camera_link->get_current_view().getCenter()) {
    window             = window_link;
    camera             = camera_link;
    this->engine_stats = engine_stats_link;
    delta_time         = 0;
    FPS_timer.start();

    for (char i = 0; i < 2; i++)
        for (char j = 0; j < 2; j++)
            active_chunks.push_back(new Chunk(generator, 16 * i, 16 * j));
}
scene::GameScene::~GameScene() {
    for (const auto chunk : active_chunks)
        delete chunk;
}


void scene::GameScene::render() {
    delta_time = FPS_timer.restart().asSeconds();
    for (const auto chunk : active_chunks)
        window->draw(*chunk);

    handle_player();
    handle_camera();
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
        player.move({x, -y}, delta_time);
    player.render(window);
}

void scene::GameScene::handle_camera() const {
    const auto distance = player.getPosition() - camera->get_current_view().getCenter(),
               delta = exp(distance.length() * distance_multiplier) * camera_speed * delta_time * distance.normalized();

    cout << "camera move call:\n\t\t"
    << "distance: {" << distance.x << ';' << distance.y << "}\n\t\t"
    << "delta: {" << delta.x << ';' << delta.y << "}\n\n";

    if (distance.length() > 1.5)
        camera->move(delta);
}

void scene::GameScene::update() {}

bool scene::GameScene::event(const Event &event) {
    bool updated = false;

    return updated;
}

void scene::GameScene::reseed(const long long generator_seed) {
    generator.reseed(generator_seed);
}

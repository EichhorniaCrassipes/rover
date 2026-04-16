#include "gameScene.h"

#include <iostream>
using std::cout;

#include <cmath>
using std::exp;
using std::abs;

#include <SFML/Window/Keyboard.hpp>

#include "../../objects/map/chunk.h"
#include "../../objects/map/block.h"
#include "../../objects/map/stone.h"

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
    blocks.push_back(new Stone({1, 2},"test0", 0));
    blocks.push_back(new Stone({3.5, 1}, "test1", 0));
}
scene::GameScene::~GameScene() {
    for (const auto chunk : active_chunks)
        delete chunk;
}


void scene::GameScene::render() {
    delta_time = FPS_timer.restart().asSeconds();
    for (const auto chunk : active_chunks)
        window->draw(*chunk);
    for (const auto block : blocks)
        block->render(window);


    const auto move_vector = get_move_vector();
    handle_player(move_vector);
    handle_camera(move_vector);
}

Vector2f scene::GameScene::get_move_vector() {
    float x = 0, y = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        y = 1;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        y = -1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        x = 1;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        x = -1;

    return {x, -y};
}

void scene::GameScene::handle_player(const Vector2f &move_vector) {
    if (move_vector.length() > 0)
        player.move(move_vector, delta_time);
    player.render(window);
}

void scene::GameScene::handle_camera(const Vector2f &move_vector) {
    const auto distance = player.getPosition() - camera->get_current_view().getCenter(),
               distance_norm = distance.normalized();
    auto delta = Vector2f(0, 0);

    if (abs(distance.x) >= distance_threshold)
        delta.x = exp(distance.length() * distance_multiplier) * camera_speed * delta_time * distance_norm.x;
    if (abs(distance.y) >= distance_threshold)
        delta.y = exp(distance.length() * distance_multiplier) * camera_speed * delta_time * distance_norm.y;
    // (distance.normalized() + move_vector.normalized() * move_vector_multiplier);

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

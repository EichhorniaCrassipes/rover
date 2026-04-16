#include "gameScene.h"

#include <algorithm>
#include <iostream>
using std::cout;

#include <cmath>
using std::exp;
using std::abs;

#include <SFML/Window/Keyboard.hpp>

#include "../../generator/chunk.h"
#include "../../generator/chunkDecorations.h"
#include "../../objects/map/block.h"

scene::GameScene::GameScene(RenderWindow* window_link, Camera* camera_link, EngineStats* engine_stats_link) : generator(0),
                                                                                                              player(camera_link->get_current_view().getCenter()) {
    window             = window_link;
    camera             = camera_link;
    this->engine_stats = engine_stats_link;
    delta_time         = 0;
    FPS_timer.start();

    for (char i = 0; i < 4; i++)
        for (char j = 0; j < 4; j++) {
            active_chunks.push_back(new generator::Chunk(&generator, 16 * i, 16 * j));
            active_decoration_chunks.push_back(new generator::ChunkDecorations(&generator, 16 * i, 16 * j));
        }
}
scene::GameScene::~GameScene() {
    for (const auto chunk : active_chunks)
        delete chunk;
    for (const auto chunk : active_decoration_chunks)
        delete chunk;
}


void scene::GameScene::render() {
    delta_time = FPS_timer.restart().asSeconds();
    for (const auto chunk : active_chunks)
        window->draw(*chunk);
    for (const auto chunk : active_decoration_chunks)
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

void scene::GameScene::update() {
   for (int i = - (int)render_distance; i < render_distance; i ++)
       for (int j = -(int)render_distance; j < render_distance; j ++)
       {
           Vector2i playerChunk = {(int)std::floor(player.getPosition().x / 16.0) * 16,(int)std::floor(player.getPosition().x / 16.0) * 16};
           Vector2i Pos = {i * 16 + playerChunk.x, j * 16 + playerChunk.y};
           bool flag = false;
           for (auto it = active_chunks.begin(); it != active_chunks.end() && !flag; ++it)
           {
               auto chunk = *it;
               if ((-Vector2i{8 ,8} + chunk->getCenterPosition()) == Pos) {
                   flag = true;
               }
           }
           if (!flag)
           {
               std::cout << Pos.x/16.0 << " " << Pos.y/16.0 << std::endl;
               active_chunks.push_back(new generator::Chunk(&generator, Pos.x/16, Pos.y/16));
               active_chunks.pop_front();
           }

       }


}

bool scene::GameScene::event(const Event &event) {
    bool updated = false;
    if (const auto* wheelScrolled = event.getIf<sf::Event::MouseWheelScrolled>()) {
        if (wheelScrolled->wheel == sf::Mouse::Wheel::Vertical) {
            camera->zoom(1 - wheelScrolled->delta*zoom_coefficient);
            render_distance *= (1 - wheelScrolled->delta*zoom_coefficient);
        }
    }
    return updated;
}

void scene::GameScene::reseed(const long long generator_seed) {
    generator.reseed(generator_seed);
}

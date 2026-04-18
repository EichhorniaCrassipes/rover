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

scene::GameScene::GameScene(RenderWindow* window_link, Camera* camera_link, EngineStats* engine_stats_link,  map<string, Texture*>* textures) : generator(0),
                                                                                                            player(camera_link->get_current_view().getCenter()),
                                                                                                            scene_textures(textures)
{
    window             = window_link;
    camera             = camera_link;
    this->engine_stats = engine_stats_link;
    delta_time         = 0;
    FPS_timer.start();

    for (int i = - static_cast<int>(render_distance); i < static_cast<int>(render_distance)*2; i++)
        for (int j = - static_cast<int>(render_distance); j < static_cast<int>(render_distance); j++) {
            active_chunks.push_back(new generator::Chunk(&generator, 16 * i, 16 * j, (*scene_textures)["textures/test01.png"]));
            active_decoration_chunks.push_back(new generator::ChunkDecorations(&generator, 16 * i, 16 * j, (*scene_textures)["textures/deco01.png"]));
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
    /*for (const auto block : blocks)
        block->render(window);
    */

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
    update_chunks();

}

bool scene::GameScene::event(const Event &event) {
    bool updated = false;
    if (const auto* wheelScrolled = event.getIf<sf::Event::MouseWheelScrolled>()) {
        if (wheelScrolled->wheel == sf::Mouse::Wheel::Vertical) {
            camera->zoom(1 - wheelScrolled->delta*zoom_coefficient);
            //render_distance *= (1 - wheelScrolled->delta*zoom_coefficient);
        }
    }
    return updated;
}

void scene::GameScene::reseed(const long long generator_seed) {
    generator.reseed(generator_seed);
}

void scene::GameScene::update_chunks()
{
    const Vector2i playerChunk = {static_cast<int>(std::floor(player.getPosition().x / 64 / 16.0)) * 16,static_cast<int>(std::floor(player.getPosition().y / 64 / 16.0)) * 16};
    for (int i = - static_cast<int>(render_distance) + 1; i < static_cast<int>(render_distance); i ++)
        for (int j = - static_cast<int>(render_distance) + 1; j < static_cast<int>(render_distance); j ++)
        {
            const Vector2i Pos = {i * 16 + playerChunk.x, j * 16 + playerChunk.y};
            bool flag = false;
            for (auto it = active_chunks.begin(); it != active_chunks.end() && !flag; ++it)
            {
                auto chunk = *it;
                if ((chunk->getAbsolutePosition()) == Pos) {
                    flag = true;
                }
            }
            if (!flag)
            {
                //std::cout << Pos.x << " " << Pos.y << std::endl;
                active_chunks.push_back(new generator::Chunk(&generator, Pos.x, Pos.y, (*scene_textures)["textures/test01.png"]));
                active_decoration_chunks.push_back(new generator::ChunkDecorations(&generator, Pos.x, Pos.y, (*scene_textures)["textures/deco01.png"]));

            }

        }

    for (auto it = active_chunks.begin(); it != active_chunks.end(); ++it)
    {
        auto chunk = *it;
        if ((static_cast<sf::Vector2f>((chunk->getAbsolutePosition()) - playerChunk)).length() > render_distance * 2 * 16) {
            std::cout << "distance between player and deleted chunk" << (static_cast<sf::Vector2f>((chunk->getAbsolutePosition()) - playerChunk)).length();
            delete chunk;
            active_chunks.erase(it);
        }
    }
    for (auto it = active_decoration_chunks.begin(); it != active_decoration_chunks.end(); ++it)
    {
        auto chunk = *it;
        if ((static_cast<sf::Vector2f>((chunk->getAbsolutePosition()) - playerChunk)).length() > render_distance * 2 * 16) {
            delete chunk;
            active_decoration_chunks.erase(it);
        }
    }
}
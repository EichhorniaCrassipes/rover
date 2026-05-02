#include "gameScene.h"

#include "../../engine/libraries.h"
#include "../../objects/ui/ghost.h"

#include <iostream>
using std::cout;

#include <cmath>
using std::exp;
using std::abs;

#include <SFML/Window/Keyboard.hpp>

#include "../../engine/enums.h"

#include "../../generator/chunks/chunk.h"
#include "../../generator/chunks/chunkDecorations.h"


scene::GameScene::GameScene(
    RenderWindow* window_link,
    Camera* camera_link,
    EngineStats* engine_stats_link
) : Scene(window_link, engine_stats_link),
    generator(0),
    player(camera_link->get_current_view().getCenter(), default_player_speed),
    mouse_object(nullptr)
{
    camera     = camera_link;
    delta_time = 0;
    FPS_timer.start();
    first_start = false;
    mouse_object = new Ghost("drill", {1,1});
}
scene::GameScene::~GameScene() {
    for (const auto chunk : active_chunks)
        delete chunk;
    for (const auto chunk : active_decoration_chunks)
        delete chunk;
    for (const auto block : blocks)
        delete block;
}

void scene::GameScene::on_start() {
    if (!first_start) {
        for (int i = -static_cast<int>(render_distance); i < static_cast<int>(render_distance); i++)
            for (int j = -static_cast<int>(render_distance); j < static_cast<int>(render_distance); j++) {
                active_chunks.push_back(new generator::Chunk(&generator, 16 * i, 16 * j, &game::TEXTURE_LIBRARY["tileset"]));
                active_decoration_chunks.push_back(new generator::ChunkDecorations(&generator, 16 * i, 16 * j, &game::TEXTURE_LIBRARY["decoset"]));
            }
        entities.push_back(new object::Entity("spawn", {0,0}, 0));
        first_start = true;
    }
}
void scene::GameScene::on_end() {
    window->setView(window->getDefaultView());
}


void scene::GameScene::render() {
    delta_time = FPS_timer.restart().asSeconds();
    for (const auto chunk : active_chunks)
        window->draw(*chunk);
    for (const auto chunk : active_decoration_chunks)
        window->draw(*chunk);
    for (const auto entity : entities) {
        window->draw(*entity);
    }
    window->draw(*mouse_object);

    const auto move_vector = get_move_vector();
    const bool does_sprint = get_sprint_trigger();
    handle_player(move_vector, does_sprint);
    handle_camera(move_vector);
}

Vector2f scene::GameScene::get_move_vector() {
    float x = 0, y = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        y = -1;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        y = 1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        x = 1;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        x = -1;

    return {x, y};
}
bool scene::GameScene::get_sprint_trigger() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift))
        return true;
    return false;
}

void scene::GameScene::handle_player(const Vector2f &move_vector, const bool &sprint) {
    if (sprint) player.setSpeed(sprint_player_speed);
    else player.setSpeed(default_player_speed);

    if (move_vector.length() > 0)
        player.move(move_vector, delta_time);
    window->draw(player);
}

void scene::GameScene::handle_camera(const Vector2f &move_vector) const {
    const auto distance = player.getPosition() + (player.getSprite().getGlobalBounds().size) / 2.f - camera->get_current_view().getCenter(),
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
    player.updateCollisionList(entities);
    const auto absolute_mouse_coords = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    mouse_coords_rounded = sf::Vector2f(
        std::floor(absolute_mouse_coords.x / 64.0f) * 64.0f,
        std::floor(absolute_mouse_coords.y / 64.0f) * 64.0f);
    mouse_object->setPosition(mouse_coords_rounded/2.f);
    //std::cout << "rounded mouse coordinates: " << mouse_coords_rounded.x << "  " << mouse_coords_rounded.y << std::endl;
}

scene::Status scene::GameScene::event(const Event &event) {
    if (const auto* wheelScrolled = event.getIf<Event::MouseWheelScrolled>())
        if (wheelScrolled->wheel == sf::Mouse::Wheel::Vertical)
            camera->zoom(1 - wheelScrolled->delta*zoom_coefficient);

    mouse_object->updateCollisionList(entities);
    if (mouse_object->checkCollision()) {
        mouse_object->updateShader("red");
    }
    else {
        mouse_object->updateShader("green");
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
            entities.push_back(new object::Entity("drill", mouse_coords_rounded, 0));
    }

    return {false, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};
}


void scene::GameScene::update_chunks() {
    const Vector2i playerChunk = {
        static_cast<int>(std::floor(player.getPosition().x / 64 / 16.0)) * 16,
        static_cast<int>(std::floor(player.getPosition().y / 64 / 16.0)) * 16
    };
    for (int i = -static_cast<int>(render_distance) + 1; i < static_cast<int>(render_distance); i++)
        for (int j = -static_cast<int>(render_distance) + 1; j < static_cast<int>(render_distance); j++) {
            const Vector2<long long> Pos = {i * 16 + playerChunk.x, j * 16 + playerChunk.y};
            bool flag = false;

            for (auto it = active_chunks.begin(); it != active_chunks.end() && !flag; ++it)
                if (const auto chunk = *it; chunk->getAbsolutePosition() == Pos)
                    flag = true;

            if (!flag) {
                active_chunks.push_back(new generator::Chunk(&generator, Pos.x, Pos.y, &game::TEXTURE_LIBRARY["tileset"]));
                active_decoration_chunks.push_back(new generator::ChunkDecorations(&generator, Pos.x, Pos.y, &game::TEXTURE_LIBRARY["decoset"]));
            }

        }

    for (auto it = active_chunks.begin(); it != active_chunks.end(); ++it) {
        const auto chunk = *it;
        const auto delta_vector = static_cast<Vector2f>(
            chunk->getAbsolutePosition() - static_cast<Vector2<long long>>(playerChunk)
        );
        if (delta_vector.lengthSquared() > render_distance_squared * 4 * 256) {
            std::cout << "[chunk/deletion] delta = " << delta_vector.length() << '\n';
            delete chunk;
            active_chunks.erase(it);
        }
    }
    for (auto it = active_decoration_chunks.begin(); it != active_decoration_chunks.end(); ++it) {
        if (const auto chunk = *it; static_cast<Vector2f>(chunk->getAbsolutePosition() - playerChunk).lengthSquared() > render_distance_squared * 4 * 256) {
            delete chunk;
            active_decoration_chunks.erase(it);
        }
    }
}


void scene::GameScene::reseed(const long long generator_seed) { generator.reseed(generator_seed); }

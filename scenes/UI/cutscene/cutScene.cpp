#include "cutScene.h"

#include <iostream>
using std::cout;

#include <SFML/System/Angle.hpp>
using sf::degrees;

#include "../../../engine/enums.h"


scene::CutScene::CutScene(RenderWindow* window_link, EngineStats* scene_index_link, const Font* font_link)
                         : UIScene(window_link, scene_index_link),
                           main_theme("music/Sand Planet.mp3"),
                           go_next_text(*font_link, "Press [Space] to continue", 20) {
    go_next_text.setFillColor({147, 147, 147});
    current_canvas = 0;


    textures[0] = {};
    sprites[0] = {};
    velocities[0] = {};

    breakers[0] = seconds(0);


    auto* texture = new Texture("cutscene/1-1.jpg");
    auto* sprite = new Sprite(*texture);
    sprite->setPosition({0, -250});
    sprite->setScale({1.4, 1.4});
    velocities[1].emplace_back(-5, 0);
    textures[1].push_back(texture);
    sprites[1].push_back(sprite);

    texture = new Texture("cutscene/1-2.png");
    sprite = new Sprite(*texture);
    sprite->setPosition({570, 400});
    sprite->setScale({.75, .75});
    velocities[1].emplace_back(8, 4);
    textures[1].push_back(texture);
    sprites[1].push_back(sprite);

    texture = new Texture("cutscene/1-3.png");
    sprite = new Sprite(*texture);
    sprite->setPosition({1870, 450});
    sprite->setScale({.3, .3});
    velocities[1].emplace_back(-4, -1);
    textures[1].push_back(texture);
    sprites[1].push_back(sprite);

    breakers[1] = seconds(0); // 11


    texture = new Texture("cutscene/2-1.jpg");
    sprite = new Sprite(*texture);
    sprite->setPosition({-20, 0});
    sprite->setScale({1.1, 1.1});
    velocities[2].emplace_back(3, 1);
    textures[2].push_back(texture);
    sprites[2].push_back(sprite);

    breakers[2] = seconds(0); // 16


    texture = new Texture("cutscene/3-1.jpg");
    sprite = new Sprite(*texture);
    sprite->setPosition({0, -250});
    sprite->setScale({1.4, 1.4});
    velocities[3].emplace_back(-5, 0);
    textures[3].push_back(texture);
    sprites[3].push_back(sprite);

    texture = new Texture("cutscene/3-2.png");
    sprite = new Sprite(*texture);
    sprite->setPosition({0, 0});
    velocities[3].emplace_back(0, 0);
    textures[3].push_back(texture);
    sprites[3].push_back(sprite);

    texture = new Texture("cutscene/3-3.png");
    sprite = new Sprite(*texture);
    sprite->setPosition({830, 700});
    sprite->setScale({.15, .15});
    sprite->setRotation(degrees(50));
    velocities[3].emplace_back(1, -3);
    textures[3].push_back(texture);
    sprites[3].push_back(sprite);

    breakers[3] = seconds(1); // 21



    // breakers[4] = seconds(31);
}
scene::CutScene::~CutScene() {
    for (unsigned i = 0; i < CANVASES; i++)
        for (unsigned j = 0; j < sprites[i].size(); j++) {
            delete sprites[i][j];
            delete textures[i][j];
        }
}

void scene::CutScene::on_start() {
    window->setView(window->getDefaultView());
    main_theme.play();
    main_theme.setVolume(0);
    timer.start();
}
void scene::CutScene::on_end() {
    main_theme.stop();
}


void scene::CutScene::render() {
    if (go_next)
        window->draw(go_next_text);

    scheduler();

    const float delta_time = timer.restart().asSeconds();
    for (unsigned i = 0; i < sprites[current_canvas].size(); i++) {
        const auto current = sprites[current_canvas][i];
        current->move(velocities[current_canvas][i] * delta_time);
        window->draw(*current);
    }
}
void scene::CutScene::update() {
    if (main_theme.getDuration() == main_theme.getPlayingOffset())
        go_next = true;
}

scene::Status scene::CutScene::event(const Event &event) {
    if (event.is<Event::KeyReleased>()) {
        const auto* keyEvent = event.getIf<Event::KeyReleased>();
        if (!keyEvent) return {false, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};

        if (keyEvent->scancode == sf::Keyboard::Scancode::Space)
            return {true, game::EXIT_SCENE, game::UI_scenes::MENU};
    }
    return {false, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};
}

void scene::CutScene::scheduler() {
    for (unsigned i = breakers.size() - 1; i > current_canvas; i--)
        if (main_theme.getPlayingOffset() >= breakers[i])
            current_canvas = i;
}

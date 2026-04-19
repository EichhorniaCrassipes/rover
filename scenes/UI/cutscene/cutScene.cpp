#include "cutScene.h"

#include <iostream>
using std::cout;

#include "../../../engine/enums.h"


scene::CutScene::CutScene(RenderWindow* window_link, EngineStats* scene_index_link, const Font* font_link)
                         : UIScene(window_link, scene_index_link),
                           main_theme("music/Sand Planet.mp3"),
                           go_next_text(*font_link, "Press [Space] to continue", 20) {
    go_next_text.setFillColor({147, 147, 147});
    current_canvas = 0;


    sprites[0] = {};
    velocities[0] = {};

    breakers[0] = seconds(10);


    auto texture = Texture("cutscene/1-1.jpg");
    auto* sprite = new Sprite(texture);
    sprite->setPosition({0, 0});
    velocities[1].emplace_back(0, 0);
    sprites[1].push_back(sprite);

    texture = Texture("cutscene/1-2.png");
    sprite = new Sprite(texture);
    sprite->setPosition({1170, 870});
    sprite->setScale({.45, .45});
    velocities[1].emplace_back(0, 0);
    sprites[1].push_back(sprite);

    texture = Texture("cutscene/1-3.png");
    sprite = new Sprite(texture);
    sprite->setPosition({1870, 450});
    sprite->setScale({.3, .3});
    velocities[1].emplace_back(0, 0);
    sprites[1].push_back(sprite);

    breakers[1] = seconds(16);


    texture = Texture("cutscene/1-3.png");
    sprite = new Sprite(texture);
    sprite->setPosition({0, 0});
    velocities[2].emplace_back(0, 0);
    sprites[2].push_back(sprite);

    breakers[2] = seconds(22);
}
scene::CutScene::~CutScene() {
    for (const auto &vs : sprites)
        for (const auto s : vs)
            delete s;
}

void scene::CutScene::on_start() {
    main_theme.play();
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
        sprites[current_canvas][i]->move(velocities[current_canvas][i] * delta_time);
        window->draw(*sprites[current_canvas][i]);
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
            return {true, game::game_scenes::RESET, game::UI_scenes::MENU};
    }
    return {false, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};
}

void scene::CutScene::scheduler() {
    for (unsigned i = breakers.size() - 1; i > current_canvas; i--)
        if (main_theme.getPlayingOffset() >= breakers[i])
            current_canvas = i;
}

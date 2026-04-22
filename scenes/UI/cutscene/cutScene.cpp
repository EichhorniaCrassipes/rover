#include "cutScene.h"

#include <iostream>
using std::cout;

#include <SFML/System/Angle.hpp>
using sf::degrees;

#include "../../../engine/enums.h"


scene::CutScene::CutScene(RenderWindow* window_link, EngineStats* scene_index_link, const Font* font_link)
                         : UIScene(window_link, scene_index_link),
                           main_theme("music/Sand Planet.mp3"),
                           go_next_text(*font_link, "Press [Space] to continue", 20),
                           RE(*font_link, "Re!", 150),
                           EngiLabs(*font_link, "by EngiLabs", 80),
                           authors(*font_link, "@GriB28\n@ArsenyKenunen\n@EichhorniaCrassipes", 45),
                           media_info(*font_link, "music: Sati Akura - Sand Planet\narts: @Ogonyok", 35),
                           concept_trailer(*font_link, "concept trailer", 20) {
    go_next_text.setFillColor({147, 147, 147});

    RE.setFillColor({237, 147, 0});
    RE.setPosition({(2560 - RE.getGlobalBounds().size.x) / 2, 350});
    EngiLabs.setFillColor({170, 170, 170});
    EngiLabs.setPosition({(2560 - EngiLabs.getGlobalBounds().size.x) / 2, 580});
    authors.setFillColor({147, 174, 74, 141});
    authors.setPosition({2000, 1250});
    media_info.setFillColor({147, 147, 147, 141});
    media_info.setPosition({10, 1310});
    concept_trailer.setFillColor({147, 147, 147, 141});
    concept_trailer.setPosition({2560 - concept_trailer.getGlobalBounds().size.x - 10, 1410});

    current_canvas = 0;

    breakers[0] = seconds(0);
    breakers[1] = seconds(11); // 11
    breakers[2] = seconds(16); // 16
    breakers[3] = seconds(21); // 21

    shattered = false;
    shattered_time = seconds(35.75);
    breakers[4] = seconds(31); // 31

    breakers[5] = seconds(41); // 41

    default_view_reset = true;
    breakers[6] = seconds(46); // 46

    is_7_canvas = false;
    breakers[7] = seconds(51.7); // 51.7

    breakers[8] = seconds(77); // 77

    breakers[9] = seconds(79.5); // 79.5
}


void scene::CutScene::on_start() {
    textures[0] = {};
    sprites[0] = {};
    velocities[0] = {};
    size_deltas[0] = {};


    auto* texture = new Texture("cutscene/1-1.jpg");
    auto* sprite = new Sprite(*texture);
    sprite->setPosition({0, -250});
    sprite->setScale({1.4, 1.4});
    velocities[1].emplace_back(-5, 0);
    size_deltas[1].emplace_back(0, 0);
    textures[1].push_back(texture);
    sprites[1].push_back(sprite);

    texture = new Texture("cutscene/1-2.png");
    sprite = new Sprite(*texture);
    sprite->setPosition({570, 400});
    sprite->setScale({.75, .75});
    velocities[1].emplace_back(8, 4);
    size_deltas[1].emplace_back(.001, .001);
    textures[1].push_back(texture);
    sprites[1].push_back(sprite);

    texture = new Texture("cutscene/1-3.png");
    sprite = new Sprite(*texture);
    sprite->setPosition({1870, 450});
    sprite->setScale({.3, .3});
    velocities[1].emplace_back(-4, -1);
    size_deltas[1].emplace_back(0, 0);
    textures[1].push_back(texture);
    sprites[1].push_back(sprite);


    texture = new Texture("cutscene/2-1.jpg");
    sprite = new Sprite(*texture);
    sprite->setPosition({-20, 0});
    sprite->setScale({1.1, 1.1});
    velocities[2].emplace_back(3, 1);
    size_deltas[2].emplace_back(0, 0);
    textures[2].push_back(texture);
    sprites[2].push_back(sprite);


    texture = new Texture("cutscene/3-1.jpg");
    sprite = new Sprite(*texture);
    sprite->setPosition({0, -250});
    sprite->setScale({1.4, 1.4});
    velocities[3].emplace_back(-5, 0);
    size_deltas[3].emplace_back(0, 0);
    textures[3].push_back(texture);
    sprites[3].push_back(sprite);

    texture = new Texture("cutscene/3-2.png");
    sprite = new Sprite(*texture);
    sprite->setPosition({0, 0});
    velocities[3].emplace_back(0, 0);
    size_deltas[3].emplace_back(0, 0);
    textures[3].push_back(texture);
    sprites[3].push_back(sprite);

    texture = new Texture("cutscene/3-3.png");
    sprite = new Sprite(*texture);
    sprite->setPosition({830, 700});
    sprite->setScale({.15, .15});
    sprite->setRotation(degrees(50));
    velocities[3].emplace_back(1, -3);
    size_deltas[3].emplace_back(-.001, -.001);
    textures[3].push_back(texture);
    sprites[3].push_back(sprite);


    texture = new Texture("cutscene/3-1.jpg");
    sprite = new Sprite(*texture);
    sprite->setPosition({0, -250});
    sprite->setScale({1.4, 1.4});
    velocities[4].emplace_back(-5, 0);
    size_deltas[4].emplace_back(0, 0);
    textures[4].push_back(texture);
    sprites[4].push_back(sprite);

    texture = new Texture("cutscene/4-2.png");
    sprite = new Sprite(*texture);
    sprite->setPosition({0, 0});
    velocities[4].emplace_back(0, 0);
    size_deltas[4].emplace_back(0, 0);
    textures[4].push_back(texture);
    sprites[4].push_back(sprite);

    texture = new Texture("cutscene/4-3.png");
    sprite = new Sprite(*texture);
    sprite->setPosition({1030, 520});
    sprite->setScale({.5, .5});
    sprite->setTextureRect({{0, 0}, {540, 460}});
    velocities[4].emplace_back(10, 2);
    size_deltas[4].emplace_back(0, 0);
    textures[4].push_back(texture);
    sprites[4].push_back(sprite);


    texture = new Texture("cutscene/5-1.jpg");
    sprite = new Sprite(*texture);
    sprite->setPosition({-250, -50});
    sprite->setScale({1.4, 1.2});
    velocities[5].emplace_back(5, 0);
    size_deltas[5].emplace_back(0, 0);
    textures[5].push_back(texture);
    sprites[5].push_back(sprite);

    texture = new Texture("cutscene/5-2.png");
    sprite = new Sprite(*texture);
    sprite->setPosition({0, 0});
    velocities[5].emplace_back(0, 0);
    size_deltas[5].emplace_back(0, 0);
    textures[5].push_back(texture);
    sprites[5].push_back(sprite);

    texture = new Texture("cutscene/5-3.png");
    sprite = new Sprite(*texture);
    sprite->setPosition({1340, 720});
    sprite->setScale({.6, .6});
    sprite->setRotation(degrees(-20));
    velocities[5].emplace_back(1, 46);
    size_deltas[5].emplace_back(0, 0);
    textures[5].push_back(texture);
    sprites[5].push_back(sprite);


    texture = new Texture("cutscene/6-1.jpg");
    sprite = new Sprite(*texture);
    sprite->setPosition({-1500, -800});
    sprite->setScale({2, 2});
    velocities[6].emplace_back(105, 0);
    size_deltas[6].emplace_back(0, 0);
    textures[6].push_back(texture);
    sprites[6].push_back(sprite);

    texture = new Texture("cutscene/6-2.png");
    sprite = new Sprite(*texture);
    sprite->setPosition({-512, -320});
    sprite->setScale({1.4, 1.4});
    velocities[6].emplace_back(0, 0);
    size_deltas[6].emplace_back(0, 0);
    textures[6].push_back(texture);
    sprites[6].push_back(sprite);

    texture = new Texture("cutscene/6-3.png");
    sprite = new Sprite(*texture);
    sprite->setPosition({1050, 500});
    sprite->setScale({.6, .6});
    velocities[6].emplace_back(0, 0);
    size_deltas[6].emplace_back(-.06, -.06);
    textures[6].push_back(texture);
    sprites[6].push_back(sprite);


    textures[7] = {};
    sprites[7] = {};
    velocities[7] = {};
    size_deltas[7] = {};


    texture = new Texture("cutscene/8-1.jpg");
    sprite = new Sprite(*texture);
    sprite->setPosition({0, 0});
    velocities[8].emplace_back(0, 0);
    size_deltas[8].emplace_back(.0015, .0015);
    textures[8].push_back(texture);
    sprites[8].push_back(sprite);


    texture = new Texture("cutscene/9-1.jpg");
    sprite = new Sprite(*texture);
    sprite->setPosition({0, 0});
    sprite->setScale({1.1, 1.1});
    velocities[9].emplace_back(0, 0);
    size_deltas[9].emplace_back(-.0015, -.0015);
    textures[9].push_back(texture);
    sprites[9].push_back(sprite);


    local_default_view = window->getDefaultView();
    local_default_view.setSize({
        2560,
        2560 / static_cast<float>(window->getSize().x) * static_cast<float>(window->getSize().y)
    });
    local_default_view.setCenter({1280, 800});

    window->setView(local_default_view);
    main_theme.play();
    main_theme.setVolume(40);
    timer.start();
}
void scene::CutScene::on_end() {
    main_theme.stop();

    for (unsigned i = 0; i < CANVASES; i++) {
        for (unsigned j = 0; j < sprites[i].size(); j++) {
            delete sprites[i][j];
            delete textures[i][j];
        }
        sprites[i].clear();
        textures[i].clear();
        velocities[i].clear();
        size_deltas[i].clear();
    }

    window->setView(window->getDefaultView());
}


void scene::CutScene::render() {
    scheduler();

    if (current_canvas == 0) {
        const auto local_time = main_theme.getPlayingOffset();

        window->draw(RE);

        if (local_time.asSeconds() >= 3.5)
            window->draw(EngiLabs);

        if (local_time.asSeconds() >= 6.1)
            window->draw(authors);

        if (local_time.asSeconds() >= 8.7) {
            window->draw(media_info);
            window->draw(concept_trailer);
        }
    }

    const float delta_time = timer.restart().asSeconds();
    for (unsigned i = 0; i < sprites[current_canvas].size(); i++) {
        const auto current = sprites[current_canvas][i];
        current->move(velocities[current_canvas][i] * delta_time);
        current->setScale(current->getScale() + size_deltas[current_canvas][i] * delta_time);
        window->draw(*current);
    }

    if (go_next)
        window->draw(go_next_text);
}
void scene::CutScene::update() {
    const auto local_time = main_theme.getPlayingOffset();
    if (shattered && local_time.asMilliseconds() == 0)
        go_next = true;

    if (!shattered && local_time >= shattered_time) {
        shattered = true;
        sprites[4].back()->setTextureRect({{0, 510}, {540, 921 - 510}});
    }

    if (breakers[7] > local_time && local_time >= breakers[6]) {
        auto view = window->getView();
        view.setSize(view.getSize() + Vector2f{3, 3});
        view.setCenter(local_default_view.getCenter());
        window->setView(view);
    }

    if (!default_view_reset) {
        default_view_reset = true;
        window->setView(local_default_view);
    }

    if (!is_7_canvas && local_time >= breakers[7]) {
        is_7_canvas = true;
        default_view_reset = false;
    }
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

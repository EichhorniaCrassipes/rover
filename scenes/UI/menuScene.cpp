//
// Created by Egor on 17.04.2026.
//
#include "menuScene.h"

#include <iostream>
using std::cout;

#include "../../engine/enums.h"
#include "../../engine/libraries.h"


scene::MenuScene::MenuScene(RenderWindow* window_link, EngineStats* scene_index_link)
    : UIScene(window_link, scene_index_link),
      title(nullptr), menu(nullptr), loading_text(nullptr), loading(false) {
    if (!background_texture.loadFromFile("image/menu9_2.jpg")) {
        cout << "[MenuScene] error loading texture image/menu9_2.jpg" << std::endl;
        return;
    }
    background.setTexture(&background_texture);
    background.setSize({static_cast<float>(engine_stats->window_width),
                        static_cast<float>(engine_stats->window_height)});

    if (!font.openFromFile("fonts/OCR A Extended Regular.ttf")) {
        cout << "[MenuScene] error loading font" << std::endl;
        return;
    }
}

scene::MenuScene::~MenuScene() {
    delete title;
    delete menu;
    delete loading_text;
}

void scene::MenuScene::on_start() {
    loading = false;
    initTitle();
    initMenu();
    initLoadingText();
}

void scene::MenuScene::initTitle() {
    delete title;
    title = new Text(font, L"Re!", 150);
    const auto bounds = title->getLocalBounds();
    title->setPosition({
        (static_cast<float>(engine_stats->window_width)  - bounds.size.x) / 2.f - bounds.position.x,
        60
    });
    title->setFillColor(sf::Color(237, 147, 0));
    title->setOutlineThickness(3);
    title->setOutlineColor(sf::Color::Black);
}

void scene::MenuScene::initMenu() {
    sf::String menu_items[] = {L"Play", L"Settings", L"About", L"Exit"};
    delete menu;
    menu = new GameMenu(
        *window,
        static_cast<float>(engine_stats->window_width),
        350,
        450,
        300,
        4,
        menu_items,
        120,
        100
    );
    menu->setColorTextMenu(sf::Color(237, 147, 0), sf::Color::Red, sf::Color::Black);
    menu->AlignMenu(2);
}

void scene::MenuScene::initLoadingText() {
    delete loading_text;
    loading_text = new Text(font, L"Loading...", 80);
    loading_text->setFillColor(sf::Color(237, 147, 0));
    loading_text->setOutlineThickness(2);
    loading_text->setOutlineColor(sf::Color::Black);
    const auto bounds = loading_text->getLocalBounds();
    loading_text->setPosition({
        (static_cast<float>(engine_stats->window_width)  - bounds.size.x) / 2.f - bounds.position.x,
        (static_cast<float>(engine_stats->window_height) - bounds.size.y) / 2.f - bounds.position.y
    });
}

void scene::MenuScene::render() {
    if (loading) {
        sf::RenderStates states;
        if (game::SHADER_LIBRARY.count("darken"))
            states.shader = &game::SHADER_LIBRARY.at("darken");
        window->draw(background, states);
        if (loading_text) window->draw(*loading_text);
    } else {
        window->draw(background);
        if (title) window->draw(*title);
        if (menu) menu->draw();
    }
}

void scene::MenuScene::update() {}

scene::Status scene::MenuScene::event(const Event &event) {
    if (loading) return {false, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};

    if (event.is<Event::KeyReleased>()) {
        const auto* keyEvent = event.getIf<Event::KeyReleased>();
        if (!keyEvent) return {false, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};

        if (keyEvent->scancode == sf::Keyboard::Scancode::Up) {
            menu->moveUp();
            return {true, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};
        }
        if (keyEvent->scancode == sf::Keyboard::Scancode::Down) {
            menu->moveDown();
            return {true, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};
        }
        if (keyEvent->scancode == sf::Keyboard::Scancode::Enter) {
            switch (menu->getSelectedMenu()) {
                case 0: // Play
                    loading = true;
                    render();
                    window->display();
                    window->clear();
                    return {false, game::game_scenes::MAIN, game::UI_scenes::GAME};
                case 1: // Settings
                    return {false, game::DO_NOT_UPDATE_SCENE, game::UI_scenes::SETTINGS};
                case 2: // About
                    return {false, game::DO_NOT_UPDATE_SCENE, game::UI_scenes::ABOUT};
                case 3: // Exit
                    return {false, game::EXIT_SCENE, game::EXIT_SCENE};
                default:
                    return {false, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};
            }
        }
    }
    return {false, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};
}

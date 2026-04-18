//
// Created by Egor on 17.04.2026.
//
#include "menuScene.h"

#include <iostream>
using std::cout;

#include "../../engine/enums.h"


scene::MenuScene::MenuScene(RenderWindow* window_link, EngineStats* scene_index_link)
    : UIScene(window_link, scene_index_link), title(nullptr), menu(nullptr) {
    // Load background texture
    if (!background_texture.loadFromFile("image/menu9_2.jpg")) {
        cout << "[MenuScene] error loading texture image/menu9_2.jpg" << std::endl;
        return;
    }
    background.setTexture(&background_texture);
    background.setSize({static_cast<float>(engine_stats->window_width),
                        static_cast<float>(engine_stats->window_height)});

    // Load font
    if (!font.openFromFile("fonts/OCR A Extended Regular.ttf")) {
        cout << "[MenuScene] error loading font" << std::endl;
        return;
    }
}
scene::MenuScene::~MenuScene() {
    delete title;
    delete menu;
}

void scene::MenuScene::on_start() {
    initTitle();
    initMenu();
}

void scene::MenuScene::initTitle() {
    delete title;
    title = new Text(font, L"Re!", 150);
    title->setPosition({480, 50});
    title->setFillColor(sf::Color(237, 147, 0));
    title->setOutlineThickness(3);
    title->setOutlineColor(sf::Color::Black);
}

void scene::MenuScene::initMenu() {
    sf::String menu_items[] = {L"Play", L"Settings", L"About", L"Exit"};
    delete menu;
    menu = new GameMenu(*window, 950, 350, 450, 300, 4, menu_items, 120, 100);
    menu->setColorTextMenu(sf::Color(237, 147, 0), sf::Color::Red, sf::Color::Black);
    menu->AlignMenu(2);
}

void scene::MenuScene::render() {
    window->draw(background);
    if (title) window->draw(*title);
    if (menu) menu->draw();
}

void scene::MenuScene::update() {
    // No per-tick update needed for menu
}

scene::Status scene::MenuScene::event(const Event &event) {
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
            const auto &[game_scene, ui_scene] = handleMenuAction(menu->getSelectedMenu());
            return {false, game_scene, ui_scene};
        }
    }
    return {false, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};
}

pair<unsigned short, unsigned short> scene::MenuScene::handleMenuAction(int selected_menu) {
    switch (selected_menu) {
        case 0: // Play
            return {game::game_scenes::MAIN, game::UI_scenes::GAME};
        case 1: // Settings
            // TODO: Open settings scene
            return {game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};
        case 2: // About
            // TODO: Open about scene
            return {game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};
        case 3: // Exit
            return {game::EXIT_SCENE, game::EXIT_SCENE};
        default:
            return {game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};
    }
}

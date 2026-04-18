//
// Created by Egor on 17.04.2026.
//
#include "menuScene.h"

#include <iostream>
using std::cout;

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

    initTitle();
    initMenu();
}

scene::MenuScene::~MenuScene() {
    delete title;
    delete menu;
}

void scene::MenuScene::initTitle() {
    title = new Text(font, L"Re!", 150);
    title->setPosition({480, 50});
    title->setFillColor(sf::Color(237, 147, 0));
    title->setOutlineThickness(3);
    title->setOutlineColor(sf::Color::Black);
}

void scene::MenuScene::initMenu() {
    sf::String menu_items[] = {L"Play", L"Settings", L"About", L"Exit"};
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
    // No per-frame update needed for menu
}

bool scene::MenuScene::event(const sf::Event& event) {
    if (event.is<sf::Event::KeyReleased>()) {
        const auto* keyEvent = event.getIf<sf::Event::KeyReleased>();
        if (!keyEvent) return false;

        if (keyEvent->scancode == sf::Keyboard::Scancode::Up) {
            menu->moveUp();
            return true;
        }
        if (keyEvent->scancode == sf::Keyboard::Scancode::Down) {
            menu->moveDown();
            return true;
        }
        if (keyEvent->scancode == sf::Keyboard::Scancode::Enter) {
            handleMenuAction(menu->getSelectedMenu());
            return true;
        }
    }
    return false;
}

void scene::MenuScene::handleMenuAction(int selected_menu) {
    switch (selected_menu) {
    case 0: // Play
        engine_stats->current_scene_index = game::scenes::MAIN_GAME;
        break;
    case 1: // Settings
        // TODO: Open settings scene
        break;
    case 2: // About
        // TODO: Open about scene
        break;
    case 3: // Exit
        window->close();
        break;
    }
}

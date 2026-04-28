#include "settingsScene.h"

#include <iostream>
using std::cout;

#include "../../engine/enums.h"
#include "../../engine/libraries.h"


scene::SettingsScene::SettingsScene(RenderWindow* window_link, EngineStats* scene_index_link)
    : UIScene(window_link, scene_index_link), title(nullptr), hint(nullptr)
{
    if (!background_texture.loadFromFile("image/menu9_2.jpg"))
        cout << "[SettingsScene] error loading texture image/menu9_2.jpg" << std::endl;
    background.setTexture(&background_texture);
    background.setSize({static_cast<float>(engine_stats->window_width),
                        static_cast<float>(engine_stats->window_height)});

    if (!font.openFromFile("fonts/OCR A Extended Regular.ttf"))
        cout << "[SettingsScene] error loading font" << std::endl;
}

scene::SettingsScene::~SettingsScene()
{
    delete title;
    delete hint;
}

void scene::SettingsScene::on_start()
{
    initText();
}

void scene::SettingsScene::initText()
{
    delete title;
    title = new Text(font, L"Settings", 150);
    title->setFillColor(sf::Color(237, 147, 0));
    title->setOutlineThickness(3);
    title->setOutlineColor(sf::Color::Black);
    const auto title_bounds = title->getLocalBounds();
    title->setPosition({
        (static_cast<float>(engine_stats->window_width)  - title_bounds.size.x) / 2.f,
        static_cast<float>(engine_stats->window_height) * 0.15f
    });

    delete hint;
    hint = new Text(font, L"Press [Escape] to go back", 40);
    hint->setFillColor(sf::Color(200, 200, 200, 180));
    hint->setOutlineThickness(1);
    hint->setOutlineColor(sf::Color::Black);
    const auto hint_bounds = hint->getLocalBounds();
    hint->setPosition({
        (static_cast<float>(engine_stats->window_width) - hint_bounds.size.x) / 2.f,
        static_cast<float>(engine_stats->window_height) * 0.88f
    });
}

void scene::SettingsScene::render()
{
    sf::RenderStates states;
    if (game::SHADER_LIBRARY.count("darken"))
        states.shader = &game::SHADER_LIBRARY.at("darken");
    window->draw(background, states);
    if (title) window->draw(*title);
    if (hint)  window->draw(*hint);
}

void scene::SettingsScene::update() {}

scene::Status scene::SettingsScene::event(const Event& event)
{
    if (event.is<sf::Event::KeyReleased>()) {
        const auto* key = event.getIf<sf::Event::KeyReleased>();
        if (!key) return {false, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};

        if (key->scancode == sf::Keyboard::Scancode::Escape)
            return {true, game::DO_NOT_UPDATE_SCENE, game::UI_scenes::MENU};
    }
    return {false, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};
}

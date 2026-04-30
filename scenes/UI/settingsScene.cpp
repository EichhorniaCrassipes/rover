#include "settingsScene.h"

#include <iostream>
using std::cout;

#include "../../engine/enums.h"
#include "../../engine/libraries.h"

static const int   FPS_OPTION_COUNT  = 5;
static const int   fps_options[]     = {30, 60, 90, 120, 0};       // 0 = vsync
static const char* fps_labels[]      = {"30 FPS", "60 FPS", "90 FPS", "120 FPS", "VSync"};


scene::SettingsScene::SettingsScene(RenderWindow* window_link, EngineStats* scene_index_link)
    : UIScene(window_link, scene_index_link),
      title(nullptr), hint(nullptr),
      selected_item(0), fps_index(2), applied_fps_index(2)
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
    for (auto* t : row_texts) delete t;
}

void scene::SettingsScene::on_start()
{
    fps_index = applied_fps_index;
    selected_item = 0;
    initText();
    initRows();
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
        static_cast<float>(engine_stats->window_height) * 0.05f
    });

    delete hint;
    hint = new Text(font, L"Left/Right: Change    Enter: Apply    Esc: Back", 36);
    hint->setFillColor(sf::Color(200, 200, 200, 180));
    hint->setOutlineThickness(1);
    hint->setOutlineColor(sf::Color::Black);
    const auto hint_bounds = hint->getLocalBounds();
    hint->setPosition({
        (static_cast<float>(engine_stats->window_width) - hint_bounds.size.x) / 2.f,
        static_cast<float>(engine_stats->window_height) * 0.88f
    });
}

void scene::SettingsScene::initRows()
{
    for (auto* t : row_texts) delete t;
    row_texts.clear();

    const float w           = static_cast<float>(engine_stats->window_width);
    const float h           = static_cast<float>(engine_stats->window_height);
    const float row_y_start = h * 0.45f;
    const float row_spacing = h * 0.12f;
    const unsigned row_size = static_cast<unsigned>(h * 0.055f);

    const int ROW_COUNT = 1;
    row_texts.reserve(ROW_COUNT);
    for (int i = 0; i < ROW_COUNT; i++) {
        auto* t = new Text(font, buildRowString(i), row_size);
        t->setOutlineThickness(1);
        t->setOutlineColor(sf::Color::Black);
        const auto bounds = t->getLocalBounds();
        t->setPosition({
            (w - bounds.size.x) / 2.f - bounds.position.x,
            row_y_start + i * row_spacing - bounds.position.y
        });
        row_texts.push_back(t);
        //delete t; // IDK why but settings crash when t is deleting so затерпим memory leak и тд
    }
    updateRowColors();
}

sf::String scene::SettingsScene::buildRowString(int row_index) const
{
    if (row_index == 0)
        return sf::String("FPS Limit:    < ") + fps_labels[fps_index] + "  >";
    return sf::String("???");
}

void scene::SettingsScene::updateRowColors()
{
    for (int i = 0; i < static_cast<int>(row_texts.size()); i++) {
        if (i == selected_item)
            row_texts[i]->setFillColor(sf::Color(237, 147, 0));
        else
            row_texts[i]->setFillColor(sf::Color::White);
    }
}

void scene::SettingsScene::applySettings() const
{
    const int fps = fps_options[fps_index];
    if (fps == 0) {
        window->setVerticalSyncEnabled(true);
        window->setFramerateLimit(0);
    } else {
        window->setVerticalSyncEnabled(false);
        window->setFramerateLimit(static_cast<unsigned>(fps));
    }
}

void scene::SettingsScene::render()
{
    sf::RenderStates states;
    if (game::SHADER_LIBRARY.count("darken"))
        states.shader = &game::SHADER_LIBRARY.at("darken");
    window->draw(background, states);

    if (title) window->draw(*title);
    if (hint)  window->draw(*hint);
    for (auto* t : row_texts) window->draw(*t);
}

void scene::SettingsScene::update() {}

scene::Status scene::SettingsScene::event(const Event& event)
{
    if (event.is<sf::Event::KeyReleased>()) {
        const auto* key = event.getIf<sf::Event::KeyReleased>();
        if (!key) return {false, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};

        const int row_count = static_cast<int>(row_texts.size());

        if (key->scancode == sf::Keyboard::Scancode::Up) {
            selected_item = (selected_item - 1 + row_count) % row_count;
            updateRowColors();
            return {true, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};
        }
        if (key->scancode == sf::Keyboard::Scancode::Down) {
            selected_item = (selected_item + 1) % row_count;
            updateRowColors();
            return {true, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};
        }
        if (key->scancode == sf::Keyboard::Scancode::Left) {
            if (selected_item == 0)
                fps_index = (fps_index - 1 + FPS_OPTION_COUNT) % FPS_OPTION_COUNT;
            initRows();
            return {true, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};
        }
        if (key->scancode == sf::Keyboard::Scancode::Right) {
            if (selected_item == 0)
                fps_index = (fps_index + 1) % FPS_OPTION_COUNT;
            initRows();
            return {true, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};
        }
        if (key->scancode == sf::Keyboard::Scancode::Enter) {
            applySettings();
            applied_fps_index = fps_index;
            return {true, game::DO_NOT_UPDATE_SCENE, game::UI_scenes::MENU};
        }
        if (key->scancode == sf::Keyboard::Scancode::Escape) {
            fps_index = applied_fps_index;
            return {true, game::DO_NOT_UPDATE_SCENE, game::UI_scenes::MENU};
        }
    }
    return {false, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};
}

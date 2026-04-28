#include "gameUIScene.h"

#include <iostream>
using std::cout;

#include "../../engine/enums.h"

scene::GameUIScene::GameUIScene(RenderWindow* window_link, EngineStats* scene_index_link)
    : UIScene(window_link, scene_index_link), inv(nullptr), exit_dialog(nullptr), exit_flag(false)
{
    if (!font.openFromFile("fonts/OCR A Extended Regular.ttf"))
        cout << "[GameUIScene] error loading font" << std::endl;
}

scene::GameUIScene::~GameUIScene()
{
    delete inv;
    delete exit_dialog;
}

void scene::GameUIScene::on_start()
{
    exit_flag = false;
    initInventory();
    initExitDialog();
}

void scene::GameUIScene::initInventory()
{
    delete inv;

    const int   slot_count  = 5;
    const float slot_size   = 70.f;
    const float slot_gap    = 8.f;
    const float total_width = slot_count * slot_size + (slot_count - 1) * slot_gap;
    const float x           = (engine_stats->window_width  - total_width) / 2.f;
    const float y           = engine_stats->window_height - slot_size - 20.f;

    inv = new GameInventory(*window, x, y, slot_count, slot_size, slot_gap);
}

void scene::GameUIScene::initExitDialog()
{
    delete exit_dialog;
    exit_dialog = new Text(font, "Are you sure you want to exit?\n[Y]es  [N]o\nWe will miss you", 28);
    exit_dialog->setFillColor(sf::Color::White);
    exit_dialog->setOutlineThickness(1.f);
    exit_dialog->setOutlineColor(sf::Color::Black);

    const auto bounds = exit_dialog->getLocalBounds();
    exit_dialog->setPosition({
        (static_cast<float>(engine_stats->window_width)  - bounds.size.x) / 2.f,
        (static_cast<float>(engine_stats->window_height) - bounds.size.y) / 2.f
    });
}

void scene::GameUIScene::render()
{
    const auto saved_view = window->getView();
    window->setView(window->getDefaultView());

    if (inv)                       inv->draw();
    if (exit_flag && exit_dialog)  window->draw(*exit_dialog);

    window->setView(saved_view);
}

void scene::GameUIScene::update() {}

scene::Status scene::GameUIScene::event(const Event& event)
{
    //exit dialog
    if (event.is<sf::Event::KeyPressed>()) {
        const auto* key = event.getIf<sf::Event::KeyPressed>();
        if (!key) return {false, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};

        if (key->scancode == sf::Keyboard::Scancode::Escape) {
            exit_flag = true;
            return {true, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};
        }
        if (exit_flag) {
            if (key->scancode == sf::Keyboard::Scancode::Y) {
                exit_flag = false;
                return {true, game::game_scenes::RESET, game::UI_scenes::MENU};
            }
            if (key->scancode == sf::Keyboard::Scancode::N) {
                exit_flag = false;
                return {true, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};
            }
        }
    }

    //inventory
    if (event.is<sf::Event::KeyReleased>()) {
        const auto* key = event.getIf<sf::Event::KeyReleased>();
        if (!key) return {false, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};

        using sc = sf::Keyboard::Scancode;
        switch (key->scancode) {
            case sc::Num1: inv->selectSlot(0); return {true, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};
            case sc::Num2: inv->selectSlot(1); return {true, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};
            case sc::Num3: inv->selectSlot(2); return {true, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};
            case sc::Num4: inv->selectSlot(3); return {true, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};
            case sc::Num5: inv->selectSlot(4); return {true, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};
            default: break;
        }
    }

    return {false, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};
}

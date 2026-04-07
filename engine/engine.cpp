#include "engine.h"
using sf::VideoMode;
using sf::Event;

#include <iostream>
using std::cerr;
using std::to_string;

#include "enums.h"
#include "stats.h"
EngineStats game::global_stats {scenes::CUTSCENE, 0, 0};

#include "../scenes/UI/testScene.h"


game::Engine::Engine() : Engine(DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_TITLE) {}
game::Engine::Engine(const string &name) : Engine(DEFAULT_WIDTH, DEFAULT_HEIGHT, name) {}
game::Engine::Engine(const unsigned short width, const unsigned short height) : Engine(width, height, DEFAULT_TITLE) {}
game::Engine::Engine(const unsigned short width, const unsigned short height, const string &name) : FPS(default_monospace_font, "", 10),
                                                                                                    FPS_delta(default_monospace_font, "", 10),
                                                                                                    TPS(default_monospace_font, "", 10),
                                                                                                    TPS_delta(default_monospace_font, "", 10),
                                                                                                    mouse_position(default_monospace_font, "", 10),
                                                                                                    scene_num(default_monospace_font, "", 10),
                                                                                                    version(default_monospace_font, "v0.0-indev", 12) {
    window = new RenderWindow(
        VideoMode({width, height}),
        name
    );
    global_stats.window_height = height;
    global_stats.window_width = width;

    game_scenes = new scene::GameScene*[scenes::CAP];
    UI_scenes   = new scene::UIScene*[scenes::CAP];

    if (!default_monospace_font.openFromFile("fonts/OCR A Extended Regular.ttf")) {}

    FPS.setFillColor({147, 147, 147, 241});
    frames = 0;
    last_fps_update_value = 0;

    TPS.setFillColor({147, 147, 147, 241});
    ticks = 0;
    last_tps_update_value = 0;
    current_real_TPS = 0;

    mouse_position.setFillColor({147, 147, 147, 141});
    scene_num.setFillColor({147, 147, 147, 141});
    version.setFillColor({147, 147, 147, 141});
}

game::Engine::~Engine() {
    for (unsigned short i = 0; i < scenes::CAP; i++) {
        delete game_scenes[i];
        delete UI_scenes[i];
    }
    delete[] game_scenes;
    delete[] UI_scenes;

    delete window;
}

void game::Engine::run(const short fps) {
    game_scenes[scenes::LOADING]   = nullptr;
    game_scenes[scenes::MAIN_MENU] = nullptr;
    game_scenes[scenes::CUTSCENE]  = nullptr;
    game_scenes[scenes::MAIN_GAME] = new scene::GameScene(window, &global_stats);

    UI_scenes[scenes::LOADING]   = new scene::UIScene(window, &global_stats);
    UI_scenes[scenes::MAIN_MENU] = new scene::UIScene(window, &global_stats);
    UI_scenes[scenes::CUTSCENE]  = new scene::TestScene(window, &global_stats);
    UI_scenes[scenes::MAIN_GAME] = new scene::UIScene(window, &global_stats);

    if (fps > 0) window->setFramerateLimit(fps);
    else window->setVerticalSyncEnabled(true);

    TPS_timer.start();
    TPS_adjuster_timer.start();
    count_display_timer.start();
    loop();
}

void game::Engine::loop() {
    while (window->isOpen()) {
        window->clear();
        const auto current_UI_scene = UI_scenes[global_stats.current_scene_index];
        const auto current_game_scene = game_scenes[global_stats.current_scene_index];

        while (const auto event = window->pollEvent()) {
            if (event->is<Event::Closed>())
                window->close();

            try {
                bool UI_event_update = false;
                if (current_UI_scene != nullptr)
                    UI_event_update = current_UI_scene->event(*event);
                if (!UI_event_update && current_game_scene != nullptr)
                    current_game_scene->event(*event);
            }
            catch (const std::runtime_error &e) {
                cerr << e.what() << '\n';
            }
        }

        info_overdraw();

        render(current_game_scene, current_UI_scene);
        update(current_game_scene, current_UI_scene);
        window->display();

        adjust_tps();
    }
}
void game::Engine::render(scene::GameScene *game, scene::UIScene *ui) {
    if (game != nullptr)
        game->render();
    if (ui != nullptr)
        ui->render();
    frames++;
}
void game::Engine::update(scene::GameScene *game, scene::UIScene *ui) {
    if (TPS_timer.getElapsedTime() >= TPS_delta_time) {
        TPS_timer.restart();
        if (game != nullptr)
            game->update();
        if (ui != nullptr)
            ui->update();
        ticks++;
    }
}


void game::Engine::adjust_tps() {
    if (adjustment_proceeding) {
        if (TPS_adjuster_timer.getElapsedTime() >= TPS_adjuster_delta_time_flag) {
            TPS_adjuster_timer.restart();
            const float local_middle = (left_target + right_target) / 2;
            TPS_delta_time = sf::seconds(1 / local_middle);
            std::cout << "new delta time: " << TPS_delta_time.asSeconds() << std::endl;
            adjustment_proceeding = false;
        }
    }
    else {
        if (TPS_adjuster_timer.getElapsedTime() >= TPS_adjuster_delta_time) {
            TPS_adjuster_timer.restart();
            std::cout << "adjuster called\n";
            if (TPS_value - epsilon >= current_real_TPS || current_real_TPS >= TPS_value + epsilon) {
                std::cout << "adjustment started...\n";
                adjustment_proceeding = true;
                left_target = current_real_TPS * 1.2f;
                right_target = TPS_value * 2 - current_real_TPS;
                std::cout << "left target: " << left_target << ", right target: " << right_target << std::endl;
            }
        }
    }
}

void game::Engine::info_overdraw() {
    if (count_display_timer.getElapsedTime().asMilliseconds() >= 500) {
        frames = static_cast<unsigned short>(static_cast<float>(frames) / count_display_timer.getElapsedTime().asSeconds());
        current_real_TPS = static_cast<float>(ticks) / count_display_timer.getElapsedTime().asSeconds();
        ticks  = static_cast<unsigned short>(current_real_TPS);

        const auto window_x_max_coord = window->getView().getCenter().x + static_cast<float>(global_stats.window_width) / 2,
                   window_y_max_coord = window->getView().getCenter().y + static_cast<float>(global_stats.window_height) / 2;


        if (last_fps_update_value < frames)
            FPS_delta.setFillColor({0, 147, 20, 141});
        else if (last_fps_update_value > frames)
            FPS_delta.setFillColor({255, 29, 0, 141});
        else
            FPS_delta.setFillColor({147, 147, 147, 141});

        FPS.setString("FPS:" + to_string(frames));
        FPS.setPosition({window_x_max_coord - 45, 5});
        FPS_delta.setString(
            (frames - last_fps_update_value > 0 ? "(+" : "(")
            + to_string(frames - last_fps_update_value) + ')'
            );
        FPS_delta.setPosition({window_x_max_coord - 40, 15});

        if (last_tps_update_value < ticks)
            TPS_delta.setFillColor({0, 147, 20, 141});
        else if (last_tps_update_value > ticks)
            TPS_delta.setFillColor({255, 29, 0, 141});
        else
            TPS_delta.setFillColor({147, 147, 147, 141});

        TPS.setString("TPS:" + to_string(ticks));
        TPS.setPosition({window_x_max_coord - 45, 30}); // -10
        TPS_delta.setString(
            (ticks - last_tps_update_value > 0 ? "(+" : "(")
            + to_string(ticks - last_tps_update_value) + ')'
            );
        TPS_delta.setPosition({window_x_max_coord - 40, 40});

        last_fps_update_value = frames;
        last_tps_update_value = ticks;
        frames = 0;
        ticks = 0;
        count_display_timer.restart();

        const auto local_mouse_position = sf::Mouse::getPosition(*window);
        mouse_position.setString(
            to_string(local_mouse_position.x)
            + "\n ~\n"
            + std::to_string(local_mouse_position.y)
            );
        mouse_position.setPosition({window_x_max_coord - 35, 55});

        scene_num.setPosition({window_x_max_coord - 30, 90});
        scene_num.setString(to_string(global_stats.current_scene_index));

        version.setPosition({window_x_max_coord - window->getSize().x + 5, window_y_max_coord - 15});
    }

    window->draw(FPS);
    window->draw(FPS_delta);
    window->draw(TPS);
    window->draw(TPS_delta);
    window->draw(mouse_position);
    window->draw(scene_num);
    window->draw(version);
}

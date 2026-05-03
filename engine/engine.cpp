#include "engine.h"
using sf::VideoMode;
using sf::Event;

#include <iostream>
using std::cerr;
using std::cout;
using std::to_string;
using std::runtime_error;

#include "enums.h"
#include "stats.h"
#include "libraries.h"

EngineStats game::global_stats {0, 0};

#include <SFML/System/Time.hpp>
using sf::seconds;

#include "../scenes/UI/menuScene.h"
// #include "../scenes/UI/cutscene/cutScene.h"
#include "../scenes/UI/gameUIScene.h"
#include "../scenes/UI/settingsScene.h"
#include "../scenes/UI/aboutScene.h"


game::Engine::Engine() : Engine(DEFAULT_TITLE) {}
game::Engine::Engine(const string &name)
{
    const auto video_mode = VideoMode::getDesktopMode();
    window = new RenderWindow(
        video_mode,
        name,
        sf::Style::Default,
        sf::State::Fullscreen
    );
    cameras = new Camera*[game_scenes::CAP];

    global_stats.window_width = video_mode.size.x;
    global_stats.window_height = video_mode.size.y;

    game_scenes = new scene::GameScene*[game_scenes::CAP];
    UI_scenes   = new scene::UIScene*[UI_scenes::CAP];

    current_game_scene = nullptr;
    current_UI_scene = nullptr;
    current_camera = nullptr;
    current_game_scene_index = -1;
    current_UI_scene_index = -1;

    if (!default_monospace_font.openFromFile("fonts/OCR A Extended Regular.ttf"))
        cerr << "Failed to load OCRA font\n";

    FPS = new Text(default_monospace_font, "", 10);
    FPS_delta = new Text(default_monospace_font, "", 10);
    TPS = new Text(default_monospace_font, "", 10);
    TPS_delta = new Text(default_monospace_font, "", 10);
    mouse_position = new Text(default_monospace_font, "", 10);
    scene_num = new Text(default_monospace_font, "", 10);
    version = new Text(default_monospace_font, "v0.1-demo", 12);

    info_texts = {FPS, FPS_delta, TPS, TPS_delta, mouse_position, scene_num, version};

    FPS->setFillColor({147, 147, 147, 241});
    frames = 0;
    last_fps_update_value = 0;

    TPS->setFillColor({147, 147, 147, 241});
    ticks = 0;
    last_tps_update_value = 0;
    current_real_TPS = 0;

    mouse_position->setFillColor({147, 147, 147, 141});
    scene_num->setFillColor({147, 147, 147, 141});
    version->setFillColor({147, 147, 147, 141});
}

game::Engine::~Engine() {
    for (unsigned i = 0; i < game_scenes::CAP; i++) {
        delete game_scenes[i];
        delete cameras[i];
    }
    for (unsigned i = 0; i < UI_scenes::CAP; i++)
        delete UI_scenes[i];

    delete[] game_scenes;
    delete[] UI_scenes;
    delete[] cameras;

    for (const auto t : info_texts)
        delete t;

    delete window;
}

void game::Engine::run(const short fps) {
    cameras[game_scenes::RESET] = nullptr;
    cameras[game_scenes::MAIN]  = new Camera(window);

    cameras[game_scenes::MAIN]->zoom(32 * 64 / static_cast<float>(global_stats.window_width));

    game_scenes[game_scenes::RESET] = nullptr;
    game_scenes[game_scenes::MAIN]  = new scene::GameScene(window, cameras[game_scenes::MAIN], &global_stats);

    UI_scenes[UI_scenes::RESET]    = nullptr;
    UI_scenes[UI_scenes::MENU]     = new scene::MenuScene(window, &global_stats);
    UI_scenes[UI_scenes::CUTSCENE] = nullptr; //new scene::CutScene(window, &global_stats, &default_monospace_font);
    UI_scenes[UI_scenes::GAME]     = new scene::GameUIScene(window, &global_stats);
    UI_scenes[UI_scenes::SETTINGS] = new scene::SettingsScene(window, &global_stats);
    UI_scenes[UI_scenes::ABOUT]    = new scene::AboutScene(window, &global_stats);

    if (fps > 0) window->setFramerateLimit(fps);
    else window->setVerticalSyncEnabled(true);

    if (sf::Shader::isAvailable()) {
        auto& darken = game::SHADER_LIBRARY["darken"];
        if (!darken.loadFromFile("shaders/darken.frag", sf::Shader::Type::Fragment))
            cerr << "[SHADER_LIBRARY] failed to load shaders/darken.frag\n";
        else
            darken.setUniform("texture", sf::Shader::CurrentTexture);
        auto& greenshader = game::SHADER_LIBRARY["green"];
        if (!greenshader.loadFromFile("shaders/green.frag", sf::Shader::Type::Fragment))
            cerr << "[SHADER_LIBRARY] failed to load shaders/green.frag\n";
        else
            darken.setUniform("texture", sf::Shader::CurrentTexture);
        auto& redshader = game::SHADER_LIBRARY["red"];
        if (!redshader.loadFromFile("shaders/red.frag", sf::Shader::Type::Fragment))
            cerr << "[SHADER_LIBRARY] failed to load shaders/red.frag\n";
        else
            darken.setUniform("texture", sf::Shader::CurrentTexture);
    } else {
        cerr << "[SHADER_LIBRARY] shaders not supported on this system\n";
    }

    change_scene(game_scenes::RESET, UI_scenes::MENU);

    TPS_timer.start();
    TPS_adjuster_timer.start();
    count_display_timer.start();
    loop();
}

void game::Engine::loop() {
    while (window->isOpen()) {
        window->clear();

        while (const auto event = window->pollEvent()) {
            if (event->is<Event::Closed>())
                window->close();

            scene::Status UI_event_update{};
            if (current_UI_scene != nullptr) {
                try {
                    UI_event_update = current_UI_scene->event(*event);
                    change_scene(UI_event_update.next_game_scene, UI_event_update.next_UI_scene);
                }
                catch (const runtime_error &e) {
                    cout << "[UI event update] got an error while handling an event:\n";
                    cerr << e.what() << '\n';
                }
            }
            if (!UI_event_update.updated && current_game_scene != nullptr) {
                try {
                    const auto &[updated, next_game, next_UI] = current_game_scene->event(*event);
                    change_scene(next_game, next_UI);
                }
                catch (const runtime_error &e) {
                    cout << "[game event update] got an error while handling an event:\n";
                    cerr << e.what() << '\n';
                }
            }
        }

        render();
        update();

        info_update_values();
        if (current_UI_scene_index != UI_scenes::CUTSCENE)
            info_overdraw();
        window->display();

        adjust_tps();
    }
}
void game::Engine::render() {
    if (current_game_scene != nullptr) {
        try {
            current_game_scene->render();
        }
        catch (const runtime_error &e) {
            cerr << "[game render] got an error while trying to render a scene:\n";
            cerr << e.what() << '\n';
        }
    }
    if (current_UI_scene != nullptr) {
        try {
            current_UI_scene->render();
        }
        catch (const runtime_error &e) {
            cerr << "[UI render] got an error while trying to render a scene:\n";
            cerr << e.what() << '\n';
        }
    }
    if (current_camera != nullptr) {
        try {
            current_camera->apply();
        }
        catch (const runtime_error &e) {
            cout << "[camera apply call] got an error while trying to apply camera settings:\n";
            cerr << e.what() << '\n';
        }
    }
    frames++;
}
void game::Engine::update() {
    if (TPS_timer.getElapsedTime() >= TPS_delta_time) {
        TPS_timer.restart();
        if (current_game_scene != nullptr) {
            try {
                current_game_scene->update();
            }
            catch (const runtime_error &e) {
                cout << "[game updater] got an error while trying to update a scene:\n";
                cerr << e.what() << '\n';
            }
        }
        if (current_UI_scene != nullptr) {
            try {
                current_UI_scene->update();
            }
            catch (const runtime_error &e) {
                cout << "[UI updater] got an error while trying to update a scene:\n";
                cerr << e.what() << '\n';
            }
        }
        ticks++;
    }
}

void game::Engine::change_scene(const unsigned short next_game, const unsigned short next_UI) {
    if (next_game == EXIT_SCENE || next_UI == EXIT_SCENE)
        window->close();

    else {
        if (next_game != DO_NOT_UPDATE_SCENE) {
            if (current_game_scene != nullptr)
                current_game_scene->on_end();

            current_camera           = cameras[next_game];
            current_game_scene       = game_scenes[next_game];
            current_game_scene_index = next_game;

            if (current_game_scene != nullptr)
                current_game_scene->on_start();
        }
        if (next_UI != DO_NOT_UPDATE_SCENE) {
            if (current_UI_scene != nullptr)
                current_UI_scene->on_end();

            current_UI_scene = UI_scenes[next_UI];
            current_UI_scene_index = next_UI;

            if (current_UI_scene != nullptr)
                current_UI_scene->on_start();
        }
    }
}


void game::Engine::adjust_tps() {
    if (adjustment_proceeding) {
        if (TPS_adjuster_timer.getElapsedTime() >= TPS_adjuster_delta_time_flag) {
            TPS_adjuster_timer.restart();
            const float local_middle = (left_target + right_target) / 2;
            TPS_delta_time = seconds(1 / local_middle);
            cout << "[TPS adjuster] new delta time: " << TPS_delta_time.asSeconds() << '\n';
            adjustment_proceeding = false;
        }
    }
    else if (TPS_adjuster_timer.getElapsedTime() >= TPS_adjuster_delta_time) {
        TPS_adjuster_timer.restart();
        cout << "[TPS adjuster] called\n";
        if (TPS_value - epsilon >= current_real_TPS || current_real_TPS >= TPS_value + epsilon) {
            adjustment_proceeding = true;
            left_target = current_real_TPS * 1.2f;
            right_target = TPS_value * 2 - current_real_TPS;
            cout << "\tleft target: " << left_target << "\n\tright target: " << right_target << '\n';
        }
    }
}

void game::Engine::info_update_values() {
    if (count_display_timer.getElapsedTime().asMilliseconds() >= 500) {
        frames = static_cast<unsigned short>(static_cast<float>(frames) / count_display_timer.getElapsedTime().asSeconds());
        current_real_TPS = static_cast<float>(ticks) / count_display_timer.getElapsedTime().asSeconds();
        count_display_timer.restart();

        ticks  = static_cast<unsigned short>(current_real_TPS);

        if (last_fps_update_value < frames)
            FPS_delta->setFillColor({0, 147, 20, 141});
        else if (last_fps_update_value > frames)
            FPS_delta->setFillColor({255, 29, 0, 141});
        else
            FPS_delta->setFillColor({147, 147, 147, 141});

        FPS->setString("FPS:" + to_string(frames));
        FPS_delta->setString(
            (frames - last_fps_update_value > 0 ? "(+" : "(")
            + to_string(frames - last_fps_update_value) + ')'
            );

        if (last_tps_update_value < ticks)
            TPS_delta->setFillColor({0, 147, 20, 141});
        else if (last_tps_update_value > ticks)
            TPS_delta->setFillColor({255, 29, 0, 141});
        else
            TPS_delta->setFillColor({147, 147, 147, 141});

        TPS->setString("TPS:" + to_string(ticks));
        TPS_delta->setString(
            (ticks - last_tps_update_value > 0 ? "(+" : "(")
            + to_string(ticks - last_tps_update_value) + ')'
            );

        last_fps_update_value = frames;
        last_tps_update_value = ticks;
        frames = 0;
        ticks = 0;

        const auto local_mouse_position = sf::Mouse::getPosition(*window);
        mouse_position->setString(
            to_string(local_mouse_position.x)
            + "\n ~\n"
            + to_string(local_mouse_position.y)
            );
        scene_num->setString(to_string(current_game_scene_index) + ", " + to_string(current_UI_scene_index));
    }
}

void game::Engine::info_overdraw() const {
    const View current_view          = window->getView();
    const Vector2f current_view_size = current_view.getSize();
    const float window_x_max_coord   = current_view.getCenter().x + current_view_size.x / 2,
                window_y_min_coord   = current_view.getCenter().y - current_view_size.y / 2;

    FPS->setPosition({window_x_max_coord - 45, window_y_min_coord + 5});
    FPS_delta->setPosition({window_x_max_coord - 40, window_y_min_coord + 15});

    TPS->setPosition({window_x_max_coord - 45, window_y_min_coord + 30});
    TPS_delta->setPosition({window_x_max_coord - 40, window_y_min_coord + 40});

    mouse_position->setPosition({window_x_max_coord - 35, window_y_min_coord + 55});
    scene_num->setPosition({window_x_max_coord - 30, window_y_min_coord + 90});
    version->setPosition({window_x_max_coord - current_view_size.x + 5, window_y_min_coord + current_view_size.y - 15});

    for (const auto t : info_texts)
        window->draw(*t);
}

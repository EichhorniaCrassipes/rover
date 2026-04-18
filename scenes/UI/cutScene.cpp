#include "cutScene.h"

#include <iostream>
using std::cout;

#include "../../engine/enums.h"


scene::CutScene::CutScene(RenderWindow* window_link, EngineStats* scene_index_link, const Font* font_link)
                         : UIScene(window_link, scene_index_link),
                           main_theme("music/intro.mp3"),
                           go_next_text(*font_link, "Press [Space] to continue", 20) {
    go_next_text.setFillColor({147, 147, 147});
}

void scene::CutScene::on_start() {
    main_theme.play();
}
void scene::CutScene::on_end() {
    main_theme.stop();
}


void scene::CutScene::render() {
    if (go_next)
        window->draw(go_next_text);

    else {
        // cutscene proceeding
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

        if (keyEvent->scancode == sf::Keyboard::Scancode::Space) {
            // skip cutscene
            return {true, game::game_scenes::MAIN, game::UI_scenes::GAME};
        }
    }
    return {false, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};
}

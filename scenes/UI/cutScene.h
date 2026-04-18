#ifndef CUTSCENE_H
#define CUTSCENE_H

#include "UIScene.h"

#include <SFML/Audio/Music.hpp>
using sf::Music;

#include <SFML/Graphics/Text.hpp>
using sf::Text;
using sf::Font;

namespace scene {
    class CutScene : public UIScene {
    public:
        explicit CutScene(RenderWindow* window_link, EngineStats* scene_index_link, const Font* font_link);

        void on_start() override;
        void on_end() override;

        void render() override;
        void update() override;
        Status event(const Event &event) override;
    private:
        Music main_theme;
        bool go_next = false;

        Text go_next_text;
    };
}

#endif

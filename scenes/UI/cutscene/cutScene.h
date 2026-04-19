#ifndef CUTSCENE_H
#define CUTSCENE_H

#include "../UIScene.h"

#include <SFML/Audio/Music.hpp>
using sf::Music;

#include <SFML/Graphics/Text.hpp>
using sf::Text;
using sf::Font;

#include <SFML/Graphics/Texture.hpp>
using sf::Texture;
using sf::Vector2f;
using sf::Drawable;
using sf::Sprite;

#include <SFML/System/Clock.hpp>
using sf::Clock;
using sf::Time;
using sf::seconds;

#include <vector>
using std::vector;

#include <array>
using std::array;


namespace scene {
    class CutScene : public UIScene {
    public:
        explicit CutScene(RenderWindow* window_link, EngineStats* scene_index_link, const Font* font_link);
        ~CutScene() override;

        void on_start() override;
        void on_end() override;

        void render() override;
        void update() override;
        Status event(const Event &event) override;
    private:
        Music main_theme;
        Clock timer;

        bool go_next = false;
        Text go_next_text;

        void scheduler();
        array<Time, 3> breakers{};

        unsigned current_canvas;
        array<vector<Sprite*>, 3> sprites;
        array<vector<Vector2f>, 3> velocities;
    };
}

#endif

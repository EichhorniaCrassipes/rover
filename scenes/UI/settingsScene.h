#ifndef ROVER_SETTINGSSCENE_H
#define ROVER_SETTINGSSCENE_H

#include "UIScene.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
using sf::RenderWindow;
using sf::Font;
using sf::Text;
using sf::Texture;
using sf::RectangleShape;

#include <vector>
using std::vector;

namespace scene {
    class SettingsScene : public UIScene {
    public:
        explicit SettingsScene(RenderWindow* window_link, EngineStats* scene_index_link);
        ~SettingsScene() override;

        void on_start() override;

        void render() override;
        void update() override;
        Status event(const Event& event) override;

    private:
        RectangleShape background;
        Texture background_texture;
        Font font;
        Text* title;
        Text* hint;

        int selected_item;
        int fps_index;
        int applied_fps_index;

        vector<Text*> row_texts;

        void initText();
        void initRows();
        void updateRowColors();
        void applySettings() const;
        sf::String buildRowString(int row_index) const;
    };
}

#endif //ROVER_SETTINGSSCENE_H

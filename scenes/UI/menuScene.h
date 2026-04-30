//
// Created by Egor on 17.04.2026.
//

#ifndef ROVER_MENUSCENE_H
#define ROVER_MENUSCENE_H

#include "UIScene.h"

#include <SFML/Graphics/RenderWindow.hpp>
using sf::RenderWindow;

#include <SFML/Graphics/Text.hpp>
using sf::Text;
using sf::Font;

#include <SFML/Graphics/RectangleShape.hpp>
using sf::RectangleShape;

#include <SFML/Graphics/Texture.hpp>
using sf::Texture;

#include "../../objects/ui/gameMenu.h"
using menu::GameMenu;

namespace scene {
    class MenuScene : public UIScene {
    public:
        explicit MenuScene(RenderWindow* window_link, EngineStats* scene_index_link);
        ~MenuScene() override;

        void on_start() override;

        void render() override;
        void update() override;
        Status event(const Event &event) override;

    private:
        RectangleShape background;
        Texture background_texture;
        Font font;
        Text* title;
        GameMenu* menu;
        Text* loading_text;
        bool loading;

        void initTitle();
        void initMenu();
        void initLoadingText();
    };
}

#endif //ROVER_MENUSCENE_H

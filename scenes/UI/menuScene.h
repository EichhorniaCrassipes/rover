//
// Created by Egor on 17.04.2026.
//

#ifndef ROVER_MENUSCENE_H
#define ROVER_MENUSCENE_H

#include "UIScene.h"

#include <SFML/Graphics/RenderWindow.hpp>
using sf::RenderWindow;

#include <SFML/Graphics/RectangleShape.hpp>
using sf::RectangleShape;

#include <SFML/Graphics/Texture.hpp>
using sf::Texture;

#include <SFML/Graphics/Font.hpp>
using sf::Font;

#include <SFML/Graphics/Text.hpp>
using sf::Text;

#include "../../objects/ui/gameMenu.h"
using menu::GameMenu;

namespace scene {
    class MenuScene : public UIScene {
    public:
        explicit MenuScene(RenderWindow* window_link, EngineStats* scene_index_link);
        ~MenuScene() override;

        void render() override;
        void update() override;
        bool event(const sf::Event& event) override;

    private:
        RectangleShape background;
        Texture background_texture;
        Font font;
        Text* title;
        GameMenu* menu;

        void initTitle();
        void initMenu();
        void handleMenuAction(int selected_menu);
    };
}

#endif //ROVER_MENUSCENE_H
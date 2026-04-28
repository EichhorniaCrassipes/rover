#ifndef ROVER_ABOUTSCENE_H
#define ROVER_ABOUTSCENE_H

#include "UIScene.h"

#include <SFML/Graphics/RenderWindow.hpp>
using sf::RenderWindow;

#include <SFML/Graphics/Font.hpp>
using sf::Font;

#include <SFML/Graphics/Text.hpp>
using sf::Text;

#include <SFML/Graphics/Texture.hpp>
using sf::Texture;

#include <SFML/Graphics/Sprite.hpp>
using sf::Sprite;

#include <SFML/Graphics/RectangleShape.hpp>
using sf::RectangleShape;

namespace scene {
    class AboutScene : public UIScene {
    public:
        explicit AboutScene(RenderWindow* window_link, EngineStats* scene_index_link);
        ~AboutScene() override;

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
        Text* description;

        Texture github_qr_texture;
        Texture itch_qr_texture;
        Sprite* github_qr;
        Sprite* itch_qr;
        Text* github_caption;
        Text* itch_caption;

        void initText();
        void initQRCodes();
        void initDescription();
    };
}

#endif //ROVER_ABOUTSCENE_H

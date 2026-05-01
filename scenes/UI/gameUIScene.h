#ifndef ROVER_GAMEUISCENE_H
#define ROVER_GAMEUISCENE_H

#include "UIScene.h"

#include <SFML/Graphics/RenderWindow.hpp>
using sf::RenderWindow;

#include <SFML/Graphics/Font.hpp>
using sf::Font;

#include <SFML/Graphics/Text.hpp>
using sf::Text;

#include "../../objects/ui/gameInventory.h"
using inventory::GameInventory;

namespace scene {
    class GameUIScene : public UIScene {
    public:
        explicit GameUIScene(RenderWindow* window_link, EngineStats* scene_index_link);
        ~GameUIScene() override;

        void on_start() override;

        void render() override;
        void update() override;
        Status event(const Event& event) override;

    private:
        GameInventory* inv;
        Font font;
        Text* exit_dialog;
        Text* stamina_bar;
        bool exit_flag;

        void initInventory();
        void initExitDialog();
        void initStaminaBar();
    };
}

#endif //ROVER_GAMEUISCENE_H

#ifndef ROVER_GAME_SCENE_H
#define ROVER_GAME_SCENE_H

#include <SFML/Window/Event.hpp>
using sf::Event;

#include <SFML/Graphics/RenderWindow.hpp>
using sf::RenderWindow;

#include <vector>
using std::vector;

#include <map>
using std::map;

#include "../../objects/block.h"
#include "../../objects/entity.h"

namespace scene {
    class GameScene {
    public:
        explicit GameScene(RenderWindow* window_link);
        virtual ~GameScene() = 0;

        void render() const;
        void update();
        bool event(const Event &event); // возвращает true, если произошла какая-либо обработка
    protected:
        RenderWindow* window;

        map<int, map<int, Block>> upper_decorations, interactive_blocks;
        vector<Entity> entities;
        // tilemap нижних декораций
        // tilemap карты
    };
}

#endif
#ifndef ROVER_GAME_SCENE_H
#define ROVER_GAME_SCENE_H

#include <SFML/Window/Event.hpp>
using sf::Event;

#include <vector>
using std::vector;

#include <map>
using std::map;

#include "../../objects/block.h"
#include "../../objects/entity.h"

namespace scene {
    class GameScene {
    public:
        GameScene() = default;
        virtual ~GameScene() = default;

        void render();
        void update();
        bool event(const Event &event); // возвращает true, если произошла какая-либо обработка
    private:
        map<int, map<int, Block>> upper_decorations, interactive_blocks;
        vector<Entity> entities;
        // tilemap нижних декораций
        // tilemap карты
    };
}

#endif
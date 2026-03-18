#ifndef ROVER_SCENE_H
#define ROVER_SCENE_H

#include <SFML/Window/Event.hpp>
using sf::Event;

namespace game {
    class Scene {
    public:
        Scene() = default;
        virtual ~Scene() = default;

        void render();
        void update();
        void event(const Event &event);
    private:
        // 3 layers of objects
        // list of entities
        // media (OST + ...)
    };
}

#endif
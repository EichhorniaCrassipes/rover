#ifndef SCENE
#define SCENE

#include <SFML/Graphics/RenderWindow.hpp>
using sf::RenderWindow;
using sf::Event;

#include "../engine/stats.h"
using game::EngineStats;

#include "status.h"


namespace scene {
    class Scene {
    public:
        Scene(RenderWindow* window_link, EngineStats* engine_stats_link);
        virtual ~Scene() = default;

        virtual void render() = 0;
        virtual void update() = 0;
        virtual Status event(const Event &event) = 0;

        virtual void on_start();
        virtual void on_end();
    protected:
        RenderWindow* window;
        EngineStats* engine_stats;
    };
}

#endif

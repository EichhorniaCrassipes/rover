#ifndef ROVER_UI_SCENE_H
#define ROVER_UI_SCENE_H

#include "../scene.h"
using sf::Event;

#include <vector>
using std::vector;

#include <map>
using std::map;

#include "../../engine/stats.h"
using game::EngineStats;

#include "../../objects/object.h"

namespace scene {
    class UIScene : public Scene {
    public:
        explicit UIScene(RenderWindow* window_link, EngineStats* scene_index_link);
        ~UIScene() override;

        void render() override;
        void update() override;
        Status event(const Event &event) override;
    protected:
        vector<sf::Drawable*> test_pull;
        // std::map<int, map<int, UIObject>> objects;
        // media (OST + ...)
    };
}

#endif

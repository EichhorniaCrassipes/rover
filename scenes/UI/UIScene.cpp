#include "UIScene.h"

scene::UIScene::UIScene(RenderWindow* window_link) {
    window = window_link;
}


void scene::UIScene::render() const {
    for (const auto o : test_pull) {
        window->draw(o->getSprite());
    }
}

void scene::UIScene::update() {}

bool scene::UIScene::event(const Event &event) { return true; }

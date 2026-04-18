#include "UIScene.h"


scene::UIScene::UIScene(RenderWindow* window_link, EngineStats* scene_index_link) : Scene(window_link, scene_index_link) {}

scene::UIScene::~UIScene() {
    for (const auto o : test_pull) delete o;
}


void scene::UIScene::render() {
    for (const auto o : test_pull)
        window->draw(*o);
}

void scene::UIScene::update() {}

bool scene::UIScene::event(const Event &event) { return false; }

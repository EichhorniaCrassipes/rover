#include "gameScene.h"

scene::GameScene::GameScene(RenderWindow* window_link, EngineStats* scene_index_link) {
    window = window_link;
    scene_index = scene_index_link;
}


void scene::GameScene::render() const {}

void scene::GameScene::update() {}

bool scene::GameScene::event(const Event &event) { return true; }

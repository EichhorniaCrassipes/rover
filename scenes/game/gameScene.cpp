#include "gameScene.h"

scene::GameScene::GameScene(RenderWindow* window_link, EngineStats* scene_index_link) {
    window = window_link;
    scene_index = scene_index_link;
    FPS_timer.start();
    delta_time = 0;
}


void scene::GameScene::render() {
    delta_time = FPS_timer.getElapsedTime().asSeconds();
    FPS_timer.restart();
}

void scene::GameScene::update() {}

bool scene::GameScene::event(const Event &event) { return true; }

#include "gameScene.h"

scene::GameScene::GameScene(RenderWindow* window_link) {
    window = window_link;
}


void scene::GameScene::render() const {}

void scene::GameScene::update() {}

bool scene::GameScene::event(const Event &event) { return true; }

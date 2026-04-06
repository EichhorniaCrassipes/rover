#include "gameScene.h"

scene::GameScene::GameScene(RenderWindow* window_link, unsigned short* scene_index_link) : gen(0)
{
    window = window_link;
    scene_index = scene_index_link;
}


void scene::GameScene::render() const {}

void scene::GameScene::update() {}

bool scene::GameScene::event(const Event &event) { return true; }

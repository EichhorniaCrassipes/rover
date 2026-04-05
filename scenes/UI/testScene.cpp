#include "testScene.h"


scene::TestScene::TestScene(RenderWindow* window_link, EngineStats* scene_index_link) : UIScene(window_link, scene_index_link) {
    test_pull.push_back(new object::Object());
}

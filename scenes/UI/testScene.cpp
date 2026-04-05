#include "testScene.h"


scene::TestScene::TestScene(RenderWindow* window_link, unsigned short* scene_index_link) : UIScene(window_link, scene_index_link) {
    test_pull.push_back(new object::Object());
}

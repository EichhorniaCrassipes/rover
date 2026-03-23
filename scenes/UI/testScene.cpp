#include "testScene.h"


scene::TestScene::TestScene(RenderWindow* window_link) : UIScene(window_link) {
    Object* test = new Object();
    test_pull.push_back(test);
}

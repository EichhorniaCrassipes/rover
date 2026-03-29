#include "testScene.h"


scene::TestScene::TestScene(RenderWindow* window_link) : UIScene(window_link) {
    test_pull.push_back(new object::Object());
}

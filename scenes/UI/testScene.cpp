#include "testScene.h"


scene::TestScene::TestScene(RenderWindow* window_link) : UIScene(window_link) {
    const Object test;
    test_pull.push_back(test);
}

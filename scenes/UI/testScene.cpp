#include "testScene.h"

#include "../../objects/map/chunk.h"


scene::TestScene::TestScene(RenderWindow* window_link, EngineStats* scene_index_link) : UIScene(window_link, scene_index_link) {
    //test_pull.push_back(new object::Object());
    test_pull.push_back(new Chunk(generator::MapGenerator(0, 1), 0, 0));
    test_pull.push_back(new Chunk(generator::MapGenerator(0, 1), 16, 0));
    test_pull.push_back(new Chunk(generator::MapGenerator(0, 1), 0, 16));
    test_pull.push_back(new Chunk(generator::MapGenerator(0, 1), 16, 16));

}

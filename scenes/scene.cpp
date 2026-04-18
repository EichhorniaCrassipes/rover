#include "scene.h"


scene::Scene::Scene(RenderWindow* window_link, EngineStats* engine_stats_link) {
    window = window_link;
    engine_stats = engine_stats_link;
}


void scene::Scene::on_start() {}
void scene::Scene::on_end() {}

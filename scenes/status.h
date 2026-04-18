#ifndef SCENE_STATUS
#define SCENE_STATUS

namespace scene {
    struct Status {
        bool updated;
        unsigned short next_game_scene, next_UI_scene;
    };
}

#endif

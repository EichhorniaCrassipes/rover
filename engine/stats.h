#ifndef ENGINE_STATS
#define ENGINE_STATS

#include "enums.h"

namespace game {
    struct EngineStats {
        unsigned short current_scene_index;
        unsigned window_width, window_height;
    };

    extern EngineStats global_stats;
}

#endif
#ifndef ENGINE_STATS
#define ENGINE_STATS

namespace game {
    struct EngineStats {
        unsigned window_width, window_height;
        float stamina = 100.f;
    };

    extern EngineStats global_stats;
}

#endif
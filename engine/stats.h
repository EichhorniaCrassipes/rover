#ifndef ENGINE_STATS
#define ENGINE_STATS

namespace game {
    struct EngineStats {
        unsigned window_width, window_height;
        float stamina = 100.f;
        float health  = 100.f;
        bool game_over         = false;
        bool restart_requested = false;
        unsigned render_distance = 10;
    };

    extern EngineStats global_stats;
}

#endif
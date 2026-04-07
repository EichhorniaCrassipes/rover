#ifndef ROVER_ENUMS_H
#define ROVER_ENUMS_H

#include <SFML/System/Time.hpp>
using sf::Time;

#include <string>
using std::string;

namespace game {
    inline unsigned short DEFAULT_WIDTH  = 1920,
                          DEFAULT_HEIGHT = 1080;
    inline string         DEFAULT_TITLE  = "ROVER";

    inline float          TPS_value      = 30;
    inline Time           TPS_delta_time = sf::seconds(1 / TPS_value);

    inline Time           TPS_adjuster_delta_time = sf::seconds(300),
                          TPS_adjuster_delta_time_flag = sf::seconds(1);
    inline double         epsilon = .1;

    namespace scenes {
        inline unsigned short CAP       = 4,
                              LOADING   = 0,
                              MAIN_MENU = 1,
                              CUTSCENE  = 2,
                              MAIN_GAME = 3;
    }
}

#endif
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

    inline unsigned short SCENES_CAP = 3;

    inline unsigned short DO_NOT_UPDATE_SCENE = -1,
                          EXIT_SCENE          = -2;
    namespace game_scenes {
        inline unsigned short CAP                 = 1,

                              MAIN                = 0;
    }
    namespace UI_scenes {
        inline unsigned short CAP                 = 2,

                              MENU                = 0,
                              CUTSCENE            = 1;
    }
}

#endif
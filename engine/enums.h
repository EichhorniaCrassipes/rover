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

    inline short          UPS            = 30;
    inline Time           UPS_delta      = sf::microseconds(1000000 / UPS);

    namespace scenes {
        inline unsigned short CAP       = 4,
                              LOADING   = 0,
                              MAIN_MENU = 1,
                              CUTSCENE  = 2,
                              MAIN_GAME = 3;
    }
}

#endif
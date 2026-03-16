#ifndef ROVER_ENUMS_H
#define ROVER_ENUMS_H

#include <SFML/System/Time.hpp>
using sf::Time;

#include <string>
using std::string;

namespace game {
    inline unsigned short DEFAULT_WIDTH  = 1920;
    inline unsigned short DEFAULT_HEIGHT = 1080;
    inline string         DEFAULT_TITLE  = "ROVER";

    inline short          SCENES_CAP     = 4;
    inline short          UPS            = 30;
    inline Time           UPS_delta      = sf::microseconds(1000000 / UPS);
}

#endif
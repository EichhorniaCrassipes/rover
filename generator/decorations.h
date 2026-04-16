#ifndef DECORATIONS
#define DECORATIONS

#include <string>
using std::string;

namespace generator {
    struct Decoration {
        string name;
        double temperature_low, temperature_high,
               humidity_low, humidity_high,
               height_low, height_high;
    };

    extern Decoration GLOBAL_DECORATIONS[1];
}

#endif
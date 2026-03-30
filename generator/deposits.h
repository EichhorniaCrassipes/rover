#ifndef DEPOSITS
#define DEPOSITS

#include <string>
using std::string;

namespace generator {
    struct Deposit {
        string name;
        double temperature_low, temperature_high,
               humidity_low, humidity_high,
               height_low, height_high;
    };

    extern Deposit GLOBAL_DEPOSITS[3];
}

#endif
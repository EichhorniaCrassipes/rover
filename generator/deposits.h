#ifndef DEPOSITS
#define DEPOSITS 3

#include <string>
using std::string;

#include <array>
using std::array;


namespace generator {
    struct Deposit {
        string name;
        double temperature_low, temperature_high,
               humidity_low, humidity_high,
               height_low, height_high;
    };

    extern array<Deposit, DEPOSITS> GLOBAL_DEPOSITS;
}

#endif

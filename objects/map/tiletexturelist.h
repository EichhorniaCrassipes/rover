#ifndef ROVER_TILETEXTURELIST_H
#define ROVER_TILETEXTURELIST_H
#include <string>
using std::string;
#include <unordered_map>


namespace texturelist {
    inline std::unordered_map<string, int> maptiles  =
    {
        {"1111", 14},
        {"0000", 15},
        {"0011", 0},
        {"1010", 1},
        {"1100", 2},
        {"0101", 3},
        {"1000", 4},
        {"0100", 5},
        {"0010", 6},
        {"0001", 7},
        {"0111", 8},
        {"1011", 9},
        {"1101", 10},
        {"1110", 11},
        {"0110", 12},
        {"1001", 13}

    };
}

#endif //ROVER_TILETEXTURELIST_H


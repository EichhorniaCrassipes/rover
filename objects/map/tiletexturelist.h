#ifndef ROVER_TILETEXTURELIST_H
#define ROVER_TILETEXTURELIST_H
#include <string>
#include <array>
#include <map>
#include <unordered_map>

struct tileTexture {
    std::string filename;
    int number;
};

namespace texturelist {
    inline std::unordered_map<std::string, tileTexture> maptiles  =
    {
        {"Yellow", tileTexture{"test0", 0}},
        {"Green", tileTexture{"test1", 0}},
        {"Green Yellow 0011", tileTexture{"test01", 0}},
        {"Green Yellow 1010", tileTexture{"test01", 1}},
        {"Green Yellow 1100", tileTexture{"test01", 2}},
        {"Green Yellow 0101", tileTexture{"test01", 3}},
        {"Green Yellow 1000", tileTexture{"test01", 4}},
        {"Green Yellow 0100", tileTexture{"test01", 5}},
        {"Green Yellow 0010", tileTexture{"test01", 6}},
        {"Green Yellow 0001", tileTexture{"test01", 7}},
        {"Green Yellow 0111", tileTexture{"test01", 8}},
        {"Green Yellow 1011", tileTexture{"test01", 9}},
        {"Green Yellow 1101", tileTexture{"test01", 10}},
        {"Green Yellow 1110", tileTexture{"test01", 11}},
        {"Green Yellow 0110", tileTexture{"test01", 12}},
        {"Green Yellow 1001", tileTexture{"test01", 13}}

    };
}

#endif //ROVER_TILETEXTURELIST_H


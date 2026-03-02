#ifndef ROVER_DECORATION_H
#define ROVER_DECORATION_H
#include "mapElement.h"

#include <iostream>
using namespace std;

class Decoration: public MapElement
{
public:
    Decoration();
    static void say();
    ~Decoration() override;
};

#endif //ROVER_DECORATION_H
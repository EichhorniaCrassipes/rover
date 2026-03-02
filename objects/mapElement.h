#ifndef ROVER_MAPELEMENT_H
#define ROVER_MAPELEMENT_H
#include "object.h"

#include <iostream>
using namespace std;

class MapElement : public Object
{
public:
    MapElement();
    static void say();
    ~MapElement() override;
};
#endif //ROVER_MAPELEMENT_H
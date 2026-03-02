#ifndef ROVER_DECORATION_H
#define ROVER_DECORATION_H
#include "mapElement.h"

#include <iostream>
using namespace std;

class Decoration: public MapElement
{
public:
    Decoration() : MapElement()
    {
        cout << "[Decoration] created!" << endl;
    }
    static void say()
    {
        cout << "[Decoration] some text!" << endl;
    }
    ~Decoration()
    {
        cout << "[Decoration] deleted!" << endl;
    }
};

#endif //ROVER_DECORATION_H
#ifndef MAP_ELEMENT
#define MAP_ELEMENT

#include "object.h"

namespace object {
    class MapElement : public Object {
    public:
        MapElement() = default;
        ~MapElement() override = default;
    };
}

#endif
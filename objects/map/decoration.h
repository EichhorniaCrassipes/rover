#ifndef DECORATION
#define DECORATION

#include "../mapElement.h"

namespace object {
    class Decoration: public MapElement {
    public:
        Decoration();
        ~Decoration() override = default;
    };
}

#endif
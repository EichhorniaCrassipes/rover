#ifndef MAP_ELEMENT
#define MAP_ELEMENT

#include "object.h"


namespace object {
    class Block : public Object {
    public:
        explicit Block(
            const string &texture_index,
            const Vector2i &sprite_size,
            const Vector2i &null_position
        );
    };
}

#endif

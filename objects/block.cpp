#include "block.h"


object::Block::Block(
    const string &texture_index,
    const Vector2i &null_position
) : Object(texture_index) {
    setPosition(static_cast<Vector2f>(null_position));
}

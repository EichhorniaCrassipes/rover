#include "block.h"


object::Block::Block(
    const string &texture_index,
    const Vector2i &sprite_size,
    const Vector2f &null_position
) : Object(texture_index, sprite_size) {
    position = null_position;
}

#include "npc.h"


object::NPC::NPC(
    const string &texture_index,
    const Vector2i &sprite_size,
    const Vector2f &null_position
) : Entity(texture_index, sprite_size, null_position) {}

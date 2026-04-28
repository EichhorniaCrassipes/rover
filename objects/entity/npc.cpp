#include "npc.h"


object::NPC::NPC(
    const string &texture_index,
    const Vector2f &null_position
) : Entity(texture_index, null_position) {}

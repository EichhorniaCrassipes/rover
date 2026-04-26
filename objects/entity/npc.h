#ifndef NPC_h
#define NPC_h

#include "../entity.h"

/* будет использовано для врагов впоследствии;
 * пока что нигде не используется
 */

namespace object {
    class NPC : public Entity {
    public:
        NPC(
            const string &texture_index,
            const Vector2i &sprite_size,
            const Vector2f &null_position
        );
    };
}

#endif
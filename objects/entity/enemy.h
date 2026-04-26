#ifndef ENEMY
#define ENEMY

#include "mob.h"

/* будет использовано для врагов впоследствии;
 * пока что нигде не используется
 */

namespace object {
    class Enemy : public Mob {
    public:
        explicit Enemy(
            const string &texture_index,
            const Vector2i &sprite_size,
            const Vector2f &null_position = {0, 0}
        );
    };
}

#endif

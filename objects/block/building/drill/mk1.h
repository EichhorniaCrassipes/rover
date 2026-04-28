#ifndef DRILL_MK1
#define DRILL_MK1

#include "../drill.h"


namespace object {
    class DrillMk1 : public Drill {
    public:
        explicit DrillMk1(const Vector2i &position);
    };
}

#endif

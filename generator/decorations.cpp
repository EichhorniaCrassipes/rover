#include "decorations.h"
using generator::Decoration;


array<Decoration, DECORATIONS> generator::GLOBAL_DECORATIONS = {
    Decoration{"stone", 0, .3, .5, 1, .8, 1},
    Decoration{"stone", .8, 1, .3, .4, .6, .8},
    Decoration{"stone", .3, .4, .2, .3, .1, .8}
};

#include "deposits.h"

generator::Deposit generator::GLOBAL_DEPOSITS[3] = {
    {"stone", .35, 1, 0, .2, 0, 1},
    {"iron", .35, 1, .2, .55, .5, 1},
    {"copper", .35, 1, 0, .35, 0, .5}
};

#include "deposits.h"
using generator::Deposit;


array<Deposit, DEPOSITS> generator::GLOBAL_DEPOSITS = {
    Deposit{"stone",  .35, .7, 0,  .2,  .95, 1},
    Deposit{"iron",   .5,  1,  .4, .55, .75, .85},
    Deposit{"coal",   .35, .7, 0,  .15, .39, .5},
    Deposit{"copper", .75, 1,  0,  .15, .5,  .61}
};

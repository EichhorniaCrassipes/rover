#include "deposits.h"
using generator::Deposit;


array<Deposit, DEPOSITS> generator::GLOBAL_DEPOSITS = {
    Deposit{"iron",   .61, .8, .4,  .5,  .75, .85},
    Deposit{"stone",  .59, .7, .15, .4,  .15, .4},
    Deposit{"coal",   .35, .5, .7,  1,   .35, .5},
    Deposit{"copper", .7,  1,  0,   .25, .5,  .71}
};

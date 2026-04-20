#include "deposits.h"
using generator::Deposit;


array<Deposit, DEPOSITS> generator::GLOBAL_DEPOSITS = {
    Deposit{"stone", .35, 1, 0, .2, 0, 1},
    Deposit{"iron", .35, 1, .2, .55, .5, 1},
    Deposit{"copper", .35, 1, 0, .35, 0, .5}
};

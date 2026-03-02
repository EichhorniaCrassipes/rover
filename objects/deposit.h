#ifndef ROVER_DEPOSIT_H
#define ROVER_DEPOSIT_H
#include "block.h"

#include <iostream>
using namespace std;

class Deposit: public Block //месторождение
{
public:
    Deposit();
    static void say();
    ~Deposit() override;
};

#endif //ROVER_DEPOSIT_H
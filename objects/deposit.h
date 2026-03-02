#ifndef ROVER_DEPOSIT_H
#define ROVER_DEPOSIT_H
#include "block.h"

#include <iostream>
using namespace std;

class Deposit: public Block //месторождение
{
public:
    Deposit() : Block()
    {
        cout << "[Deposit] created!" << endl;
    }
    static void say()
    {
        cout << "[Deposit] some text!" << endl;
    }
    ~Deposit()
    {
        cout << "[Deposit] deleted!" << endl;
    }
};

#endif //ROVER_DEPOSIT_H
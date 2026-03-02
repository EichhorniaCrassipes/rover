#include "block.h"

Block::Block()
{
    cout << "[Block] created!" << endl;
}

void Block::say()
{
    cout << "[Block] some text!" << endl;
}

Block::~Block()
{
    cout << "[Block] deleted!" << endl;
}

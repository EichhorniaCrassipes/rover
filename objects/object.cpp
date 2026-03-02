#include "object.h"

Object::Object()
{
    std::cout << "[Object] created!" << std::endl;
}
void Object::say()
{
    std::cout << "[Object] some text!" << std::endl;
}
Object::~Object()
{
    std::cout << "[Object] deleted!" << std::endl;
}
int Object::draw()
{
    return 0;// 0 for no errors
}
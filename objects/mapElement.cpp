#include "mapElement.h"

MapElement::MapElement()
{
    std::cout << "[MapElement] created!" << std::endl;
}

void MapElement::say()
{
    std::cout << "[MapElement] some text!" << std::endl;
}

MapElement::~MapElement()
{
    std::cout << "[MapElement] deleted!" << std::endl;
}

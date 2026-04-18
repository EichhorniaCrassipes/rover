//
// Created by Egor on 17.04.2026.
//

#ifndef ROVER_GAMEINVENTORY_H
#define ROVER_GAMEINVENTORY_H

#include <SFML/Graphics.hpp>
#include "../object.h"

namespace inventory
{
    class GameInventory : public object::Object
    {
        float inventorySize = 5; // размер инвентаря (кол-во предметов и тд)
        float size_font;
        int max_inventory;
        int selected_inventory;
        sf::Font inventoryFont;
        std::vector<sf::Text> inventory;
        sf::Color inventory_text_color = sf::Color::White;
        sf::Color inventory_border_color = sf::Color::Black;
        sf::Color inventory_chosen_color = sf::Color::Green;

    };
}

#endif //ROVER_GAMEINVENTORY_H
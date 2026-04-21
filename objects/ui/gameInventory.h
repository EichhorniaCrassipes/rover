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
        float inv_x, inv_y;
        float inventorySize = 5; // размер инвентаря (кол-во предметов и тд)
        int size_font;
        int max_inventory;
        int selected_inventory;
        sf::Font inventoryFont;
        std::vector<sf::Text> inventory;
        sf::Color inventory_text_color = sf::Color::White;
        sf::Color inventory_border_color = sf::Color::Black;
        sf::Color inventory_chosen_color = sf::Color::Green;

        void setInitInventory(sf::Text& text, sf::String str, float xpos, float ypos);
        sf::RenderWindow& inventorywindow;

    public:
        GameInventory(sf::RenderWindow& window, float inv_x, float inv_y, int index, sf::String name[], int size_font = 15, int step = 10);
        ~GameInventory() = default;
        void draw();
        void setColorTextInventory(sf::Color menColor, sf::Color ChoColor,
                              sf::Color BordColor);
        void AlignInventory(int pos_x);
        int getSelectedInventory();

    };
}

#endif //ROVER_GAMEINVENTORY_H
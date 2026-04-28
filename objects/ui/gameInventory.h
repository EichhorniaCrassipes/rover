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
        float slot_size;
        float slot_gap;
        int slot_count;
        int selected_slot;

        sf::RenderWindow& inventorywindow;
        std::vector<sf::RectangleShape> slots;

        sf::Color slot_color     = sf::Color(60, 60, 60, 200);
        sf::Color selected_color = sf::Color::White;
        sf::Color border_color   = sf::Color(0, 0, 0, 220);

        void buildSlots();

    public:
        GameInventory(sf::RenderWindow& window, float x, float y,
                      int slot_count = 5, float slot_size = 70.f, float slot_gap = 8.f);
        ~GameInventory() = default;

        void draw();
        void selectSlot(int index);
        void selectNext();
        void selectPrev();
        void setColorTextInventory(sf::Color slotColor, sf::Color selectedColor, sf::Color borderColor);
        int getSelectedInventory() const;
    };
}

#endif //ROVER_GAMEINVENTORY_H

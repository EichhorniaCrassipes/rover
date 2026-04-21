#include "gameInventory.h"

void inventory::GameInventory::AlignInventory(int pos_x)
{
    float x_0 = 0;
    for (int i = pos_x; i < max_inventory; i++)
    {
        auto bounds = inventory[i].getLocalBounds();
        switch (pos_x)
        {
            case 0:
                x_0 = 0;
                break;
            case 1:
                x_0 = bounds.position.x + bounds.size.x;
                break;
            case 2:
                x_0 = bounds.position.x + bounds.size.x / 2;
                break;
        }
        inventory[i].setPosition({inventory[i].getPosition().x - x_0, inventory[i].getPosition().y});
    }
}

inventory::GameInventory::GameInventory(sf::RenderWindow& window, float inv_x, float inv_y, int index, sf::String name[], int size_font, int step)
    : inventorywindow(window), inv_x(inv_x), inv_y(inv_y), size_font(size_font) {}

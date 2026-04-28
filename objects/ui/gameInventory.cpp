#include "gameInventory.h"

void inventory::GameInventory::buildSlots()
{
    slots.clear();
    slots.reserve(slot_count);

    for (int i = 0; i < slot_count; i++) {
        sf::RectangleShape slot({slot_size, slot_size});
        slot.setPosition({inv_x + i * (slot_size + slot_gap), inv_y});
        slot.setFillColor(slot_color);
        slot.setOutlineColor(border_color);
        slot.setOutlineThickness(2.f);
        slots.push_back(slot);
    }

    slots[selected_slot].setOutlineColor(selected_color);
    slots[selected_slot].setOutlineThickness(4.f);
}

inventory::GameInventory::GameInventory(sf::RenderWindow& window, float x, float y,
                                        int slot_count, float slot_size, float slot_gap)
    : inventorywindow(window), inv_x(x), inv_y(y),
      slot_size(slot_size), slot_gap(slot_gap),
      slot_count(slot_count), selected_slot(0)
{
    buildSlots();
}

void inventory::GameInventory::draw()
{
    for (const auto& slot : slots)
        inventorywindow.draw(slot);
}

void inventory::GameInventory::selectSlot(int index)
{
    if (index < 0 || index >= slot_count) return;

    slots[selected_slot].setOutlineColor(border_color);
    slots[selected_slot].setOutlineThickness(2.f);

    selected_slot = index;
    slots[selected_slot].setOutlineColor(selected_color);
    slots[selected_slot].setOutlineThickness(4.f);
}

void inventory::GameInventory::selectNext()
{
    selectSlot((selected_slot + 1) % slot_count);
}

void inventory::GameInventory::selectPrev()
{
    selectSlot((selected_slot - 1 + slot_count) % slot_count);
}

void inventory::GameInventory::setColorTextInventory(sf::Color slotColor, sf::Color selectedColor,
                                                     sf::Color borderColor)
{
    slot_color     = slotColor;
    selected_color = selectedColor;
    border_color   = borderColor;
    buildSlots();
}

int inventory::GameInventory::getSelectedInventory() const
{
    return selected_slot;
}

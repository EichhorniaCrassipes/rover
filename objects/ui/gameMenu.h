//
// Created by Egor on 16.04.2026.
//

#ifndef ROVER_GAMEMENU_H
#define ROVER_GAMEMENU_H

#include <SFML/Graphics.hpp>

#include "../object.h"

namespace menu
{
    class GameMenu : public object::Object
    {
        float max_x, menu_y, menu_width, menu_height; // размеры меню

        int menu_dist; // расстояние между пунктами меню

        int size_font; // размер шрифта для меню
        int max_menu; // максимальное число объектов меню
        int selected_menu; // номер текущего пункта меню
        sf::Font menu_font;
        std::vector<sf::Text> mainMenu;
        sf::Color menu_text_color = sf::Color::White;
        sf::Color menu_chosen_color = sf::Color::Green;
        sf::Color menu_border_color = sf::Color::Black;

        void setInitMenuText(sf::Text& text, sf::String str, float xpos, float ypos);
        sf::RenderWindow& menuwindow;

    public:
        GameMenu(sf::RenderWindow& window, float max_x, float menu_y, float menu_width, float menu_height,
            int index, sf::String name[], int size_font = 60, int step = 80);
        ~GameMenu() = default;

        void draw();
        void moveUp();
        void moveDown();
        void setColorTextMenu(sf::Color menColor, sf::Color ChoColor,
                              sf::Color BordColor);
        void AlignMenu(int pos_x);
        int getSelectedMenu()
        {
            return selected_menu;
        }

    protected:
    private:
    };
}

#endif //ROVER_GAMEMENU_H
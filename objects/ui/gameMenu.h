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
        float menu_x, menu_y, menu_width, menu_height; // размеры меню

        int menu_dist; // Расстояние между пунктами меню

        int size_font; // размер шрифта для меню
        int max_menu; // Максимальное число объектов меню
        int selected_menu; // Номер текущего пункта меню
        sf::Font menu_font; // шрифт меню
        sf::Text* mainMenu;
        // цвета для меню (цвет текста, цвет выбранного пункта, цвет обводки текста
        sf::Color menu_text_color = sf::Color::White;
        sf::Color menu_chosen_color = sf::Color::Green;
        sf::Color menu_border_color = sf::Color::Black;

        // настройка текста пунктов меню
        void setInitMenuText(sf::Text& text, sf::String str, float xpos, float ypos);
        sf::RenderWindow& menuwindow;

    public:
        GameMenu(sf::RenderWindow& window, float menu_x, float menu_y, float menu_width, float menu_height,
            int index, sf::String name[], int size_font = 60, int step = 80);
        ~GameMenu()
        {
            delete[] mainMenu;
        }

        void draw(); // отрисовка меню
        void moveUp(); // перемещение выбора меню вверх
        void moveDown(); // перемещение выбора меню вниз
        // цвет элементов меню
        void setColorTextMenu(sf::Color menColor, sf::Color ChoColor,
                              sf::Color BordColor);
        void AlignMenu(int pos_x);   // Выравнивание положения меню
        int getSelectedMenu() // возвращаем номер текущего (выбранного) элемента меню
        {
            return selected_menu;
        }

    protected:
    private:
    };
}

#endif //ROVER_GAMEMENU_H
//
// Created by Egor on 16.04.2026.
//
#include <vector>

#include "gameMenu.h"

std::vector<sf::Text> mainMenu;

// метод настройки текстовых объектов пунктов игрового меню
void menu::GameMenu::setInitMenuText(sf::Text& text, sf::String str, float xpos, float ypos)
{
    text.setFont(menu_font);
    text.setString(str);
    text.setPosition({xpos, ypos});
    text.setOutlineThickness(2);
    text.setOutlineColor(menu_border_color);
    text.setFillColor(menu_border_color);
    text.setFillColor(menu_text_color);
}

// Выравнивание пунктов меню по левому по правому по центру
void menu::GameMenu::AlignMenu(int pos_x)
{
    float x_0 = 0;
    for (int i = 0; i < max_menu; ++i)
    {
        auto bounds = mainMenu[i].getLocalBounds();
        switch (pos_x)
        {
        case 0:
            x_0 = 0; // выравнивание по правому краю от установленных координат
            break;
        case 1:
            x_0 = bounds.position.x + bounds.size.x; // по левому краю
            break;
        case 2:
            x_0 = bounds.position.x + bounds.size.x / 2; // по центру
            break;
        }
        mainMenu[i].setPosition({mainMenu[i].getPosition().x - x_0, mainMenu[i].getPosition().y});
    }
}

// Конструктор
menu::GameMenu::GameMenu(sf::RenderWindow& window, float menu_x, float menu_y, float menu_width, float menu_height, int index, sf::String name[], int size_font, int step)
    : menuwindow(window), menu_x(menu_x), menu_y(menu_y), size_font(size_font), menu_dist(step)
{
    if (!menu_font.openFromFile("fonts/OCR A Extended Regular.ttf"))
        exit(32);

    max_menu = index;

    mainMenu = std::vector<sf::Text>(max_menu, sf::Text(menu_font)).data();
    for (int i = 0, ypos = menu_y; i < max_menu; i++, ypos += menu_dist) setInitMenuText(mainMenu[i], name[i], menu_x, ypos);
    selected_menu = 0; // Задаём начальное положения выбраного пункта меню
    mainMenu[selected_menu].setFillColor(menu_border_color);
}

// перемещение выбора меню вверх
void menu::GameMenu::moveUp()
{
    selected_menu--;
    if (selected_menu >= 0) {
        mainMenu[selected_menu].setFillColor(menu_chosen_color); // подсвечиваем выбранный пункт меню
        mainMenu[selected_menu + 1].setFillColor(menu_text_color);
    }
    else
    {
        mainMenu[0].setFillColor(menu_text_color);
        selected_menu = max_menu - 1;
        mainMenu[selected_menu].setFillColor(menu_chosen_color);
    }
}
// перемещение выбора меню вниз
void menu::GameMenu::moveDown()
{
    selected_menu++;
    // подсвечиваем выбранный пункт меню
    if (selected_menu < max_menu) {
        mainMenu[selected_menu - 1].setFillColor(menu_text_color);
        mainMenu[selected_menu].setFillColor(menu_chosen_color);
    }
    else
    {
        mainMenu[max_menu - 1].setFillColor(menu_text_color);
        selected_menu = 0;
        mainMenu[selected_menu].setFillColor(menu_chosen_color);
    }
}
// рисуем элементы меню в графическом окне
void menu::GameMenu::draw()
{
    for (int i = 0; i < max_menu; i++) menuwindow.draw(mainMenu[i]);
}

void menu::GameMenu::setColorTextMenu(sf::Color textColor, sf::Color ChoColor, sf::Color BordColor)
{
    menu_text_color = textColor;
    menu_chosen_color = ChoColor;
    menu_border_color = BordColor;

    for (int i = 0; i < max_menu; i++) {
        mainMenu[i].setFillColor(menu_text_color);
        mainMenu[i].setOutlineColor(menu_border_color);
    }

    mainMenu[selected_menu].setFillColor(menu_chosen_color);
}

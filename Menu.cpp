#include "Menu.hpp"

Menu::Menu(float ancho, float alto)
{
    if (!font.loadFromFile("fonts/Times New Romance.ttf"))
    {
        cout << "No font is here";
    }

    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(Color::White);
    mainMenu[0].setString("Play");
    mainMenu[0].setCharacterSize(70);
    mainMenu[0].setPosition(75, 200);

    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(Color::White);
    mainMenu[1].setString("Options");
    mainMenu[1].setCharacterSize(70);
    mainMenu[1].setPosition(75, 300);

    mainMenu[2].setFont(font);
    mainMenu[2].setFillColor(Color::White);
    mainMenu[2].setString("Credits");
    mainMenu[2].setCharacterSize(70);
    mainMenu[2].setPosition(75, 400);

    mainMenu[3].setFont(font);
    mainMenu[3].setFillColor(Color::White);
    mainMenu[3].setString("Exit");
    mainMenu[3].setCharacterSize(70);
    mainMenu[3].setPosition(75, 500);

    menuSelected = -1;
}

void Menu::dibujar(RenderWindow &window)
{
    for (int i = 0; i < Max_main_Menu; i++)
    {
        window.draw(mainMenu[i]);
    }
}

void Menu::moveUp()
{
    if (menuSelected < 0)
        menuSelected = 0;
    mainMenu[menuSelected].setFillColor(Color::White);
    menuSelected--;
    if (menuSelected < 0)
        menuSelected = 3;
    mainMenu[menuSelected].setFillColor(Color::Green);
}

void Menu::moveDown()
{
    if (menuSelected > 3)
        menuSelected = 3;
    mainMenu[menuSelected].setFillColor(Color::White);
    menuSelected++;
    if (menuSelected > 3)
        menuSelected = 0;
    mainMenu[menuSelected].setFillColor(Color::Green);
}

int Menu::menuPressed()
{
    return menuSelected;
}

Menu::~Menu()
{
}

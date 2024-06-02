#ifndef Menu_h
#define Menu_h
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
using namespace sf;
using namespace std;

#define Max_main_Menu 4
class Menu
{
    int menuSelected; 
    Font font; 
    Text mainMenu[Max_main_Menu]; 

public: 
    Menu(float ancho, float alto); 

    void dibujar(RenderWindow& window);
    void moveUp(); 
    void moveDown(); 

    int menuPressed(); 

    ~Menu(); 
}; 

#endif 
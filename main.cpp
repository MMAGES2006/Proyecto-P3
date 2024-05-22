#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include <iostream>
using namespace std;
using namespace sf;

int numCells = 25;
int width = 500;
int height = 500;
int speed = 10;

int main()
{
    bool mousePressed = false;
    RenderWindow window(VideoMode(width, height), "SFML works!");
    window.setFramerateLimit(60);
    Grid grid(numCells, width, height);
    Texture p1Texture;
    if (p1Texture.loadFromFile("sprites/P1.png"))
    {
        cout << "Error al cargar imagen" << endl;
    }
    p1Texture.setRepeated(true);

    Sprite p1;
    p1.setTexture(p1Texture);
    p1.setTextureRect(IntRect(0, 0, 248, 243));
    p1.setScale(0.3, 0.3);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            window.clear();
            // grid.update();
            window.draw(p1);
            // grid.drawTo(window);
            window.display();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            p1.move(speed, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            p1.move(0, speed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            p1.move(-speed, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            p1.move(0, -speed);

        window.clear();
        // grid.update();
        window.draw(p1);
        // grid.drawTo(window);
        window.display();
    }
    return 0;
}
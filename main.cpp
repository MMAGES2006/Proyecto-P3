#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include <iostream>
using namespace std;
using namespace sf;

int numCells = 25;
int width = 500;
int height = 500;

int main()
{
    bool mousePressed = false;
    RenderWindow window(VideoMode(width, height), "SFML works!");
    window.setFramerateLimit(30);
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
<<<<<<< HEAD
    // p1.setScale(0.5);
=======
    p1.setScale(0.3,0.3);
>>>>>>> 495a484dcd7c085f93bb1293d08313c88764a661

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    mousePressed = true;
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;
                    grid.toggle(x, y);
                }
            }

            window.clear();
            // grid.update();
            window.draw(p1);
            // grid.drawTo(window);
            window.display();
        }
    }
    return 0;
}
#include <SFML/Graphics.hpp>
#include "Grid.hpp"
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
            /*
            else 
            {
                if(event.type == Event::MouseButtonReleased){
                    if(event.mouseButton.button == Mouse::Left)
                    {
                        mousePressed = false; 
                    }

                }

            }
            */
            }

        grid.update();
        grid.drawTo(window);
        window.display();
        }
    }
    return 0;
    }
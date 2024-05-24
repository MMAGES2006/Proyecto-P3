#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include "Player.hpp"
#include <iostream>
using namespace std;
using namespace sf;

int main()
{
    int cols = 72; //36
    int rows = 40; //20
    int pixel = 25; //50
    int width = cols*pixel;
    int height = rows*pixel;
    int speed = 5;
    bool mousePressed = false;
    bool follow = 0;
    View map, camera;
    camera.setSize(width/2, height/2);
    map.setSize(width, height);
    map.setCenter(width/2, height/2);
    RenderWindow window(VideoMode(width, height), "SFML works!");
    window.setFramerateLimit(60);
    Grid grid(cols, rows, pixel);
    Texture monkey;
    if (!monkey.loadFromFile("sprites/P1.png")) cout << "Error al cargar imagen" << '\n';
    Player player(10, 5, monkey, &grid, 100, 100);
    Clock timer;
    float time=16.67;
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
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;
                    grid.toggle(x, y);
                }
                /*if (event.mouseButton.button == Mouse::Right)
                {
                    play = !play;
                }*/
                if (event.mouseButton.button == Mouse::Right) 
                {
                    follow = !follow;
                    if(!follow) window.setView(map);
                }
            }
        }
        player.control(time);
        window.clear();
        if(follow) 
        {
            camera.setCenter(player.x, player.y);
            window.setView(camera);
        }
        //grid.update();
        grid.drawTo(window);
        player.drawTo(window);
        window.display();
        time = (timer.restart().asMilliseconds())/10;
    }
    return 0;
}
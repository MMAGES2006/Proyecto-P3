#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include <iostream>
using namespace std;
using namespace sf;

int main()  //Camera 36x20, 50 square pixels
{
    int cols = 100; //72
    int rows = 100; //40 (as long as it divides the height it should be fine)
    int pixelCamera = 50; //50
    int height = 1000;
    int pixel = height/rows;
    int fps = 60;
    int widthMap = cols*pixel;
    int widthCamera = 1800;
    float changeFactor = (float)pixel/(float)pixelCamera;
    int speed = 5;

    bool mousePressed = false;
    bool playing = 0; //booleano que contiene si se esta "jugando" o no

    View map, camera;
    map.setSize(widthMap, height);
    map.setCenter(widthMap/2, height/2);
    camera.setSize(widthCamera*changeFactor, height*changeFactor);

    RenderWindow window(VideoMode(widthMap, height), "BioThreat");
    Vector2i mapPosition = window.getPosition();
    Vector2i cameraPostion = mapPosition + Vector2i((widthMap-widthCamera)/2, 0);
    window.setFramerateLimit(fps);
    Grid grid(cols, rows, pixel, changeFactor, &playing);

    Texture monkey;
    if (!monkey.loadFromFile("sprites/P1.png")) cout << "Error al cargar imagen" << '\n';
    Player player(10, 5, monkey, &playing, &grid, 100, 100);
    
    Texture slime; 
    if (!slime.loadFromFile("sprites/slime.png")) cout << "Error al cargar imagen" << '\n';
    Enemy enemy(5, 3, slime, &grid, 500, 500); 
    
    Clock timer;
    float time = 100 / fps;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left && !playing)
                {
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;
                    grid.toggle(x, y);
                }
                if (event.mouseButton.button == Mouse::Right) //para cambiar entre que la camara te siga y ver el mapa
                {
                    playing = !playing;
                    if(playing)
                    {
                        window.setPosition(cameraPostion);
                        window.setSize(Vector2u(widthCamera, height));
                    }
                    else
                    {
                        window.setPosition(mapPosition);
                        window.setSize(Vector2u(widthMap, height));
                        window.setView(map);
                    }
                }
            }
        }
        player.control(time);
        window.clear();
        if(playing) 
        {
            camera.setCenter(player.x, player.y);
            window.setView(camera);
        }
        grid.drawTo(window);
        player.drawTo(window);
        enemy.drawTo(window);
        window.display();
        time = ((float)timer.restart().asMilliseconds())/10; //se usa para que la velocidad no sea dependiente de los fps
    }
    return 0;
}
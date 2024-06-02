#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Arma.hpp"
#include "Menu.hpp"
#include <iostream>
#include <math.h>
#include <cstdlib>

using namespace std;
using namespace sf;

int main() // Camera 36x20, 50 square pixels
{
    int cols = 180;       // 72
    int rows = 100;       // 40 (as long as it divides the height it should be fine)
    int pixelCamera = 50; // 50
    int height = 1000;
    int pixel = height / rows;
    int fps = 60;
    int widthMap = cols * pixel;
    int widthCamera = 1800;
    float changeFactor = (float)pixel / (float)pixelCamera;
    int speed = 5;
    srand(time(NULL)); 

    bool mousePressed = false;
    bool playing = 0; // booleano que contiene si se esta "jugando" o no

    View map, camera;
    map.setSize(widthMap, height);
    map.setCenter(widthMap / 2, height / 2);
    camera.setSize(widthCamera * changeFactor, height * changeFactor);

    RenderWindow window(VideoMode(widthMap, height), "BioThreat");
    Vector2i mapPosition = window.getPosition();
    Vector2i cameraPostion = mapPosition + Vector2i((widthMap - widthCamera) / 2, 0);
    window.setFramerateLimit(fps);

    RenderWindow mainMENU(VideoMode(960, 720),"Main Menu", Style::Default); 
    Menu Menu(mainMENU.getSize().x, mainMENU.getSize().y); 
    RectangleShape fondo; 
    fondo.setSize(Vector2f(960, 720)); 
    Texture ftexture; 
    if (!ftexture.loadFromFile("sprites/fondomenu .png"))
        cout << "Error al cargar imagen" << '\n'; 
    fondo.setTexture(&ftexture); 

    // Sprites
    vector<Texture> textures;
    Texture monkey;
    if (!monkey.loadFromFile("sprites/P1.png"))
        cout << "Error al cargar imagen" << '\n';
    textures.push_back(monkey);
    Texture slime;
    if (!slime.loadFromFile("sprites/slimeSF.png"))
        cout << "Error al cargar imagen" << '\n';
    textures.push_back(slime);

    Grid grid(cols, rows, pixel, changeFactor, &playing, textures);

    Player player(10, speed, monkey, &playing, &grid, grid.spawnX, grid.spawnY);
    
    Texture bala;
    if (!bala.loadFromFile("sprites/bala.png"))
        cout << "Error al cargar imagen" << '\n';
   
    Clock timer;
    float time = 100 / fps;

    while (mainMENU.isOpen())
    {
        Event event; 
        while (mainMENU.pollEvent(event))
        {
            if(event.type == Event::Closed)
            {
                mainMENU.close(); 
            }

            if(event.type == Event::KeyPressed)
            {
                if(event.key.code == Keyboard::Up)
                {
                    Menu.moveUp(); 
                    break;
                }

                if(event.key.code == Keyboard::Down)
                {
                    Menu.moveDown(); 
                    break;
                }

                if(event.key.code == Keyboard::Return)
                {
                    int mun = Menu.menuPressed(); 

                    if (mun == 0)
                    {
                        mainMENU.close(); 

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
                                    if (event.mouseButton.button == Mouse::Right) // para cambiar entre que la camara te siga y ver el mapa
                                    {
                                        playing = !playing;
                                        if (playing)
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

                            player.control(window, time);
                            grid.activeRoom->update(player.x, player.y, time);

                            window.clear();

                            if (playing)
                            {
                              camera.setCenter(player.x, player.y);
                              window.setView(camera);
                            }

                            grid.drawTo(window);
                            player.drawTo(window);
                            grid.activeRoom->drawTo(window);

                            window.display();
                            time = ((float)timer.restart().asMilliseconds()) / 10; // se usa para que la velocidad no sea dependiente de los fps

                            if(event.key.code  == Keyboard::Escape)
                            {
                                window.close();
                            }
                        }
                    }
                    else if (mun == 1)
                    {
                        RenderWindow Options(VideoMode(960 , 720), "OPTION"); 
                        while(Options.isOpen())
                        {
                            Event eventB; 
                            while (Options.pollEvent(eventB))
                            {
                                if(eventB.type == Event::Closed)
                                {
                                    Options.close(); 
                                }
                                
                                if(eventB.type == Event::KeyPressed)
                                {
                                    if(eventB.key.code == Keyboard::Escape)
                                    {
                                        Options.close(); 
                                    } 
                                }
                            }  
                            Options.clear();   
                            Options.display();  
                        }
                    }
                    else if(mun == 2)
                    {
                        RenderWindow About(VideoMode(960 , 720), "ABOUT"); 
                        while (About.isOpen())
                        {
                            Event eventC; 
                            while (About.pollEvent(eventC))
                            {
                                if(eventC.type == Event::Closed)
                                {
                                    About.close(); 
                                }

                                if(eventC.type == Event::KeyPressed)
                                {
                                    if(eventC.key.code == Keyboard::Escape)
                                    {
                                        About.close(); 
                                    }
                                }
                            }   
                            About.clear(); 
                            About.display(); 
                        }                    
                    }
                    else if(mun == 3)
                    {
                        mainMENU.close(); 
                    }
                }
            }
        }

        mainMENU.clear(); 
        mainMENU.draw(fondo); 
        Menu.dibujar(mainMENU); 
        mainMENU.display(); 
    }

    return 0;
}
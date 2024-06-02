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
    if (!ftexture.loadFromFile("sprites/fondomenu.png"))
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
    Enemy enemy(5, 3, slime, &playing, &grid, grid.spawnX, grid.spawnY);
    vector<Enemy> enemigos; 
    int spawnCounter = 5; 

    if(spawnCounter < 5)
    {
        spawnCounter++;
    }
    
    if(spawnCounter >=20)
    {
        enemigos.push_back(Enemy(enemy)); 
        spawnCounter = 0; 
    }

    
    Texture bala;
    if (!bala.loadFromFile("sprites/bala.png"))
        cout << "Error al cargar imagen" << '\n';
    Arma b1(5.f);
    vector<Arma> balas;

    Vector2f playerCenter;
    Vector2f mousePosWindow;
    Vector2f aimDir;
    Vector2f aimDirNorm;
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

                            playerCenter = Vector2f(player.x, player.y);
                            mousePosWindow = Vector2f(Mouse::getPosition(window));
                            aimDir = mousePosWindow - playerCenter;
                            float magnitude = sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
                            aimDirNorm = aimDir / magnitude;

                            if (Mouse::isButtonPressed(Mouse::Left))
                            {
                                b1.bullet.setPosition(playerCenter);
                                b1.currVelocity = aimDirNorm * b1.maxSpeed;

                                balas.push_back(Arma(b1));
                            }

                            for (size_t i = 0; i < balas.size(); i++)
                            {
                                balas[i].bullet.move(balas[i].currVelocity);

                                if (balas[i].bullet.getPosition().x < 0 || balas[i].bullet.getPosition().x > window.getSize().x || balas[i].bullet.getPosition().y < 0 || balas[i].bullet.getPosition().y > window.getSize().y)
                                {
                                    balas.erase(balas.begin() + i); 
                                }
                            }

                            player.control(time);
                            enemy.goTo(player.x, player.y, time);
                            window.clear();
                            if (playing)
                            {
                                camera.setCenter(player.x, player.y);
                                window.setView(camera);
                            }

                            grid.drawTo(window);
                            player.drawTo(window);
                            enemy.drawTo(window);
                            grid.activeRoom->drawTo(window);

                            for (size_t i = 0; i < balas.size(); i++)
                            {
                                window.draw(balas[i].bullet);
                            }
                            window.display();
                            time = ((float)timer.restart().asMilliseconds()) / 10; // se usa para que la velocidad no sea dependiente de los fps
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
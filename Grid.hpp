#ifndef Grid_h
#define Grid_h
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Room.hpp"
#include <vector>
#include <random>
using namespace sf;
using namespace std;

class Player;
class Grid
{
public:
    vector<vector<int>> map;
    vector<vector<int>> next;
    int cols, rows, pixel; //esta es una constante que se usa para que al hacer zoom (cuando la camara te sigue) los tamaños que se muestran en pantalla coincidan con los valores asignados
    float changeFactor;
    bool* playing; //es un booleano que es verdadero si se esta jugando, falso sino
    vector<Texture> textures;
    int spawnX, spawnY;
    Player* player;
    pair<int, int> newRoom;
    Room* miniMap[4][4];
    Room* activeRoom;
    Grid(int cols, int rows, int pixel, float changeFactor, bool* playing, vector<Texture> &textures); //constructor
    void generateMap(); //pretende ser una generación procedural del mapa pero esta en pañales
    void drawTo(RenderWindow  &window); //dibuja la matriz
    int identifyMap(float x, float y); //regresa el valor de la celda de la matriz con coordenadas x, y, se esta usando para detectar colisión
    void toggle(int x,int y); //usada para cambiar el estado de una celda con coordenadas x, y
    void generateExtra(RoomType type);
    void createRoom(int x, int y, RoomType type);
    bool enoughLenght(int x, int y, int lenght, RoomType fakeMap[4][4]);
    bool potentialRoom(int x, int y);
    ~Grid();
};

#endif
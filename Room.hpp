#ifndef Room_h
#define Room_h
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;

enum RoomType{SPAWN, COMBAT, SPECIAL, EXIT, VOID};
class Grid;
class Entity;
class Room
{
public:
    RoomType type;
    int subType;
    int x, y;
    int centerX, centerY;
    int width, height;
    bool visited;
    Grid* grid;
    vector<vector<int>> design;
    vector<Entity*> entities;
    Room(RoomType type, int x, int y, Grid* grid); //constructor
    void start();
    void update(RenderWindow &window);
};

#endif
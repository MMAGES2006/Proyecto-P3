#ifndef Room_h
#define Room_h
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;

enum EnemyType{SLIME, MONKEY};
enum RoomType{SPAWN, COMBAT, SPECIAL, EXIT, VOID};
class Grid;
class Entity;
class Enemy;

class Room
{
public:
    RoomType type;
    int subType;
    int x, y;
    int centerX, centerY;
    int cornerX, cornerY;
    int width, height;
    bool visited;
    Grid* grid;
    vector<vector<int>> design;
    vector<Entity*> entities;
    vector<Enemy*> enemies;
    Room(RoomType type, int x, int y, Grid* grid); //constructor
    void start();
    void update(float playerX, float playerY, float time);
    void killing();
    void drawTo(RenderWindow &window);
    void createEnemy(EnemyType type, int spawnX, int spawnY);
};

#endif
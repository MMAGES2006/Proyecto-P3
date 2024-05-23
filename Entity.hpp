#ifndef Entity_h
#define Entity_h
#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include <iostream>
#include <vector>
using namespace sf;
using namespace std;

enum Skin {monkey};
enum Direction{UP, LEFT, DOWN, RIGHT, NONE};
class Entity
{
public:
    int health, speed;
    float semiWidth, semiHeight;
    vector<bool> hitbox;
    Grid* grid;
    Sprite sprite;
    Entity(int health, int speed, Skin skin, Grid* grid, int x, int y);
    void drawTo(RenderWindow  &window);
    void update();
    bool collisionMap(float x, float y, Direction direction);
    int identifyMap(float x, float y);
};

#endif
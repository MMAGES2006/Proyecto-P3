#ifndef Entity_h
#define Entity_h
#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include <iostream>
#include <vector>
using namespace sf;
using namespace std;

enum skin {monkey};

class Entity
{
public:
    int health, speed;
    float semiWidth, semiHeight;
    Grid* grid;
    Sprite sprite;
    Entity(int health, int speed, int skin, Grid* grid, int x, int y);
    void drawTo(RenderWindow  &window);
    void update();
    bool collisionMap(float x, float y);
    int identifyCoordinates(float x, float y);
};

#endif
#ifndef Enemy_h
#define Enemy_h
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Player.hpp"
#include <vector>
using namespace sf;
using namespace std;

class Enemy : public Entity
{
public:
    Enemy(int health, int speed, Texture &texture, bool *playing, Grid *grid, int x, int y); // constructor

    void goTo(float targetX, float targetY, float time);
    void drawTo(RenderWindow  &window); //dibuja el sprite


    Enemy();
    Player *player;
};

#endif
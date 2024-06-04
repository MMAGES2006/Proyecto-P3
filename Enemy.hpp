#ifndef Enemy_h
#define Enemy_h
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Player.hpp"
#include <vector>
using namespace sf;
using namespace std;

enum Attack{MELEE, RANGED};
class Enemy : public Entity
{
public:
    Attack attackMode;
    float preferredDistance;
    Enemy(int health, int speed, Texture &texture, bool *playing, Grid *grid, int x, int y); // constructor
    Enemy(EnemyType type, int health, int speed, Texture &texture, bool *playing, Grid *grid, int x, int y);
    void goTo(float targetX, float targetY, float time);
};

#endif
#ifndef Arma_h
#define Arma_h
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Enemy.hpp"
#include <vector>
using namespace sf;
using namespace std;

struct Bullet
{
    CircleShape sprite;
    Vector2f direction;
};

class Arma
{
public:
    int damage;
    float cooldown;
    float timer;
    int municion;
    float radius;
    Entity* owner;
    vector<Bullet> bullets;
    Vector2f currVelocity;
    float speed;
    //Arma(float radius);

    Sprite sprite;
    //Arma(int damage, int cooldown, int municion, Texture &texture);
    
    Arma(int damage, int cooldown, int municion, float radius, float speed, Entity* owner);
    Arma(int damage, int cooldown, float radius, Entity* owner);

    void hit(vector<Enemy*> targets, Player* player, Direction direction);   // para melee.
    void fire(Vector2f targetPosition, Vector2f origin); // Armas de fuego.
    void efecto();   // Esta todavia no me decido si tendran efectos las armas, asi que queda por si acaso.
    void update(float time, vector<Enemy*> targets, Player* player);
    void drawTo(RenderWindow  &window);
    bool collision(Entity* target, CircleShape &circle);
    bool collisionMap(CircleShape &bullet);
};

#endif

#ifndef Arma_h
#define Arma_h
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
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
    float bulletRadius;
    Entity* owner;
    CircleShape bullet;
    vector<Bullet> bullets;
    Vector2f currVelocity;
    float maxSpeed;
    Arma(float radius);

    Sprite sprite;
    Arma(int damage, int cooldown, int municion, Texture &texture);
    
    Arma(int damage, int cooldown, int municion, float bulletRadius, float maxSpeed, Entity* owner);

    void atacar();   // para melee.
    void fire(RenderWindow &window); // Armas de fuego.
    void efecto();   // Esta todavia no me decido si tendran efectos las armas, asi que queda por si acaso.
    void update(float time);
    void drawTo(RenderWindow  &window);
};

#endif

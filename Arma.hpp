#ifndef Arma_h
#define Arma_h
#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include <vector>
using namespace sf;
using namespace std;

class Arma
{
public:
    int damage;
    float cooldown;
    int municion;

    CircleShape bullet;
    Vector2f currVelocity;
    float maxSpeed;

<<<<<<< HEAD
    Arma(float radius);
=======
    Arma(float radius, Texture &texture);
>>>>>>> 726bcb7b89cf1f85c7b635b3868255715844c066

    Sprite sprite;
    Arma(int damage, int cooldown, int municion, Texture &texture);

    void atacar();   // para melee.
    void disparar(); // Armas de fuego.
    void efecto();   // Esta todavia no me decido si tendran efectos las armas, asi que queda por si acaso.
};

#endif

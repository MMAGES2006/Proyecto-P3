#ifndef Balas_h
#define Balas_h
#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include <vector>
using namespace sf;
using namespace std;

class Balas
{
public:
    int damage;
    float cooldown;
    int municion;

    CircleShape bullet;
    Vector2f currVelocity;
    float maxSpeed;
    Balas(float radius);

    Sprite sprite;
    Balas(int damage, int cooldown, int municion, Texture &texture);

    void atacar();   // para melee.
    void disparar(); // Armas de fuego.
    void efecto();   // Esta todavia no me decido si tendran efectos las armas, asi que queda por si acaso.
};

#endif

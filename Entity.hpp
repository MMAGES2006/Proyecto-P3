#ifndef Entity_h
#define Entity_h
#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include <vector>
using namespace sf;
using namespace std;

enum Direction{UP, LEFT, DOWN, RIGHT, NONE};
class Arma;

class Entity
{
public:
    int health;
    float speed;
    float damaged;
    float x, y;
    float semiWidth, semiHeight;
    bool* playing; //es un booleano que es verdadero si se esta jugando, falso sino
    vector<bool> hitbox;
    Grid* grid;
    Arma* gun;
    Arma* coldWeapon;
    Sprite sprite;
    Entity(int health, int speed, Texture &texture, bool* playing, Grid* grid, int x, int y); //constructor
    void drawTo(RenderWindow  &window); //dibuja el sprite
    bool isDead();
    bool collisionMap(float x, float y, Direction direction); //Revisa si la entidad colisionaría con algun bloque del mapa si estuviera en coordenadas x, y, moviendose en cierta dirección
    void updateXY(); //actualiza las variables x, y para que correspondan con la posición de la entidad
};

#endif
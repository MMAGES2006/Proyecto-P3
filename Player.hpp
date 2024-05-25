#ifndef Player_h
#define Player_h
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include <vector>
using namespace sf;
using namespace std;

class Player: public Entity
{
private:

public:
    Player(int health, int speed, Texture &texture, bool* playing, Grid* grid, int x, int y); //constructor
    void control(float time); //son los controles del jugador, sus acciones (de momento solo moverse)
};

#endif
#ifndef Player_h
#define Player_h
#include "Entity.hpp"
#include "Object.hpp"
#include "Inventory.hpp"

class Player : public Entity
{
private:

public:
    float wait;
    int weapon;
    Direction direction;
    Player(int health, int speed, Texture &texture, bool *playing, Grid *grid, int x, int y); // constructor
    void control(RenderWindow &window, float time); // son los controles del jugador, sus acciones (de momento solo moverse)
    void updateRoom();

    //virtual ~Player(); 
};

#endif
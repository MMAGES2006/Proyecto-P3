#ifndef Player_h
#define Player_h
#include "Entity.hpp"
#include "Item.hpp"
// #include "Inventario.hpp"
class Player : public Entity
{
private:
    // Inventory inventory;

public:
    float wait;
    int weapon;
    Direction direction;
    Player(int health, int speed, Texture &texture, bool *playing, Grid *grid, int x, int y); // constructor
    void control(RenderWindow &window, float time);                                           // son los controles del jugador, sus acciones (de momento solo moverse)
    void updateRoom();
    void pickUpItem(const Item &item);
    FloatRect getBounds() const;
    // void showInventory() const;
};

#endif
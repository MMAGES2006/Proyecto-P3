#include "Player.hpp"

Player::Player(int health, int speed, Skin skin, Grid* grid, int x, int y): Entity(health, speed, skin, grid, x,y){}

void Player::control(float time)
{
    float displacement = this->speed*time;
    updateXY();
    if (Keyboard::isKeyPressed(Keyboard::W)) 
    {
        if(!collisionMap(this->x, this->y - displacement, UP)) sprite.move(0, -displacement);
    }
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        if(!collisionMap(this->x - displacement, this->y, LEFT)) sprite.move(-displacement, 0);
    }
    if (Keyboard::isKeyPressed(Keyboard::S))
    {
        if(!collisionMap(this->x, this->y + displacement, DOWN)) sprite.move(0, displacement);
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) 
    {
        if(!collisionMap(this->x + displacement, this->y, RIGHT)) sprite.move(displacement, 0);
    }
}
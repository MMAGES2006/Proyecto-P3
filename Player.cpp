#include "Player.hpp"

Player::Player(int health, int speed, int skin, Grid* grid, int x, int y): Entity(health, speed, skin, grid, x,y){}

void Player::control(float time)
{
    float displacement = this->speed*time;
    float x = this->sprite.getPosition().x+semiWidth;
    float y = this->sprite.getPosition().y+semiHeight;
    if (Keyboard::isKeyPressed(Keyboard::W)) 
    {
        if(!collisionMap(x, y - displacement)) sprite.move(0, -displacement);
    }
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        if(!collisionMap(x - displacement, y)) sprite.move(-displacement, 0);
    }
    if (Keyboard::isKeyPressed(Keyboard::S))
    {
        if(!collisionMap(x, y + displacement)) sprite.move(0, displacement);
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) 
    {
        if(!collisionMap(x + displacement, y)) sprite.move(displacement, 0);
    }
}
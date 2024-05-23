#include "Player.hpp"

Player::Player(int health, int speed, Skin skin, Grid* grid, int x, int y): Entity(health, speed, skin, grid, x,y){}

void Player::control(float time)
{
    float displacement = this->speed*time;
    float x = this->sprite.getPosition().x + this->semiWidth;
    float y = this->sprite.getPosition().y + this->semiHeight;
    if (Keyboard::isKeyPressed(Keyboard::W)) 
    {
        if(!collisionMap(x, y - displacement, UP)) sprite.move(0, -displacement);
    }
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        if(!collisionMap(x - displacement, y, LEFT)) sprite.move(-displacement, 0);
    }
    if (Keyboard::isKeyPressed(Keyboard::S))
    {
        if(!collisionMap(x, y + displacement, DOWN)) sprite.move(0, displacement);
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) 
    {
        if(!collisionMap(x + displacement, y, RIGHT)) sprite.move(displacement, 0);
    }
}
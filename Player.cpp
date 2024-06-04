#include "Player.hpp"
#include "Arma.hpp"

Player::Player(int health, int speed, Texture &texture, bool* playing, Grid* grid, int x, int y): 
Entity(health, speed, texture, playing, grid, x, y)
{
  this->gun = new Arma(0, 50, 10, 3, 10, this);
}

void Player::control(RenderWindow &window, float time)
{
  float displacement = this->speed*time;
  updateXY();
  updateRoom();
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
  if (Mouse::isButtonPressed(Mouse::Left))
  {
    this->gun->fire(window);
  }
  this->gun->update(time);
}

void Player::updateRoom()
{
  this->grid->newRoom.first = (4 * this->x) / (this->grid->pixel * this->grid->cols);
  this->grid->newRoom.second = (4* this->y) / (this->grid->pixel * this->grid->rows);
}
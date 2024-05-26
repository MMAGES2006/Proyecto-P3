#include "Enemy.hpp"


Enemy::Enemy(int health, int speed, Texture &texture, Grid *grid, int x, int y)
{
  this->health = health;
  this->x = x;
  this->y = y;
  this->hitbox = {0, 0, 0, 0, 0, 0};
  this->grid = grid;
  this->speed = speed * this->grid->changeFactor;
  this->sprite.setTexture(texture);
  this->sprite.setTextureRect(IntRect(0, 0, 500, 500));
  this->sprite.setScale(0.3*this->grid->changeFactor, 0.35*this->grid->changeFactor);
  this->semiWidth=this->sprite.getGlobalBounds().getSize().x/2;
  this->semiHeight=this->sprite.getGlobalBounds().getSize().y/2;
  this->sprite.setPosition(x - this->semiWidth, y - this->semiHeight);
}

void Enemy::drawTo(RenderWindow & window)
{
    window.draw(this->sprite);
}

void Enemy::update()
{
  return;
}

bool Enemy::collisionMap(float x, float y, Direction direction) //esta así para que sea más rápido, bueno, al menos creo que así es más rapido
{
  vector<bool> trapped = {1, 1, 1, 1, 1, 1};
  this->hitbox[0] = this->grid->identifyMap(x - this->semiWidth, y) > 0;
  this->hitbox[1] = this->grid->identifyMap(x, y) > 0;
  this->hitbox[2] = this->grid->identifyMap(x + this->semiWidth, y) > 0;
  this->hitbox[3] = this->grid->identifyMap(x - this->semiWidth, y + this->semiHeight) > 0;
  this->hitbox[4] = this->grid->identifyMap(x, y + this->semiHeight) > 0;
  this->hitbox[5] = this->grid->identifyMap(x + this->semiWidth, y + this->semiHeight) > 0;
  if(this->hitbox == trapped) return 0;
  switch(direction)
  {
    case UP:
      if(this->hitbox[0] || this->hitbox[1] || this->hitbox[2]) return 1;
      break;
    case LEFT:
      if(this->hitbox[0] || this->hitbox[3]) return 1;
      break;
    case DOWN:
      if(this->hitbox[3] || this->hitbox[4] || this->hitbox[5]) return 1;
      break;
    case RIGHT:
      if(this->hitbox[2] || this->hitbox[5]) return 1;
      break;
    case NONE:
      if(this->hitbox[0] || this->hitbox[1] || this->hitbox[2] || this->hitbox[3] || this->hitbox[4] || this->hitbox[5]) return 1;
      break;
  }
  return 0;
}

void Enemy::updateXY()
{
  this->x = this->sprite.getPosition().x + this->semiWidth;
  this->y = this->sprite.getPosition().y + this->semiHeight;
}
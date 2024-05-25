#include "Entity.hpp"

Entity::Entity(int health, int speed, Texture &texture, bool* playing, Grid* grid, int x, int y)
{
  string skinName;
  this->health = health;
  this->x = x;
  this->y = y;
  this->playing = playing;
  this->hitbox = {0, 0, 0, 0, 0, 0};
  this->grid = grid;
  this->speed = speed * this->grid->changeFactor;
  this->sprite.setTexture(texture);
  this->sprite.setTextureRect(IntRect(0, 0, 248, 243));
  this->sprite.setScale(0.3*this->grid->changeFactor, 0.35*this->grid->changeFactor);
  this->semiWidth=this->sprite.getGlobalBounds().getSize().x/2;
  this->semiHeight=this->sprite.getGlobalBounds().getSize().y/2;
  this->sprite.setPosition(x - this->semiWidth, y - this->semiHeight);
}

void Entity::drawTo(RenderWindow &window)
{
  window.draw(this->sprite);
}

void Entity::update()
{
  return;
}

bool Entity::collisionMap(float x, float y, Direction direction) //esta así para que sea más rápido, bueno, al menos creo que así es más rapido
{
  vector<bool> trapped = {1, 1, 1, 1, 1, 1};
  this->hitbox[0] = identifyMap(x - this->semiWidth, y) > 0;
  this->hitbox[1] = identifyMap(x, y) > 0;
  this->hitbox[2] = identifyMap(x + this->semiWidth, y) > 0;
  this->hitbox[3] = identifyMap(x - this->semiWidth, y + this->semiHeight) > 0;
  this->hitbox[4] = identifyMap(x, y + this->semiHeight) > 0;
  this->hitbox[5] = identifyMap(x + this->semiWidth, y + this->semiHeight) > 0;
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

int Entity::identifyMap(float x, float y)
{
  int indexX = x / this->grid->pixel;
  int indexY = y / this->grid->pixel;
  return this->grid->map[indexX][indexY];
}

void Entity::updateXY()
{
  this->x = this->sprite.getPosition().x + this->semiWidth;
  this->y = this->sprite.getPosition().y + this->semiHeight;
}

#include "Entity.hpp"
#include "Arma.hpp"

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
  this->sprite.setTextureRect(IntRect(0, 0, 320, 320));
  this->sprite.setScale(0.3*this->grid->changeFactor, 0.35*this->grid->changeFactor);
  this->spriteSemiX = this->sprite.getGlobalBounds().getSize().x/2;
  this->semiWidth = this->spriteSemiX;
  this->spriteSemiY = this->sprite.getGlobalBounds().getSize().y/2;
  this->semiHeight = this->spriteSemiY;
  this->setPosition(x, y);
  this->gun = NULL;
  this->coldWeapon = NULL;
  this->damaged = 0;
}

void Entity::drawTo(RenderWindow &window)
{
  window.draw(this->sprite);
  if(this->gun) this->gun->drawTo(window);
}

bool Entity::isDead()
{
  if(this->health < 1) 
  {
    if(this->gun) this->gun->bullets.clear();
    return 1;
  }
  return 0;
}

bool Entity::collisionMap(float x, float y, Direction direction) //esta así para que sea más rápido, bueno, al menos creo que así es más rapido
{
  //vector<bool> trapped = {1, 1, 1, 1, 1, 1};
  this->hitbox[0] = this->grid->identifyMap(x - this->semiWidth, y) > 0;
  this->hitbox[1] = this->grid->identifyMap(x, y) > 0;
  this->hitbox[2] = this->grid->identifyMap(x + this->semiWidth, y) > 0;
  this->hitbox[3] = this->grid->identifyMap(x - this->semiWidth, y + this->semiHeight) > 0;
  this->hitbox[4] = this->grid->identifyMap(x, y + this->semiHeight) > 0;
  this->hitbox[5] = this->grid->identifyMap(x + this->semiWidth, y + this->semiHeight) > 0;
  //if(this->hitbox == trapped) return 0;
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

void Entity::setPosition(int x, int y)
{
  this->sprite.setPosition(x * this->grid->pixel - this->spriteSemiX + (this->grid->pixel /2), y * this->grid->pixel - this->spriteSemiY + (this->grid->pixel /2));
}

void Entity::updateXY()
{
  this->x = this->sprite.getPosition().x + this->spriteSemiX;
  this->y = this->sprite.getPosition().y + this->spriteSemiY;
}

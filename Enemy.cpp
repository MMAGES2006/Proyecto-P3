#include "Enemy.hpp"

Enemy::Enemy(int health, int speed, Texture &texture, Grid *grid, int x, int y){
    string skinName;
  this->health = health;
  this->x = x;
  this->y = y;
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
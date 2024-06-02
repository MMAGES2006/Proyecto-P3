#include "Enemy.hpp"
#include "Player.hpp"

Enemy::Enemy(int health, int speed, Texture &texture, bool *playing, Grid *grid, int x, int y) : Entity(health, speed, texture, playing, grid, x, y)
{
}

void Enemy::goTo(float targetX, float targetY, float time)
{
  float displacementX = targetX - this->x;
  float displacementY = targetY - this->y;
  float magnitude = sqrt(pow(displacementX, 2) + pow(displacementY, 2));
  if(magnitude > 0)
  {
    displacementX /= magnitude;
    displacementY /= magnitude;
    displacementX *= this->speed * time;
    displacementY *= this->speed * time;
    this->sprite.move(displacementX, displacementY);
  }
  this->updateXY();
}


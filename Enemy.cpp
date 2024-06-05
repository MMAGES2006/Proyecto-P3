#include "Enemy.hpp"
#include "Player.hpp"
#include "Arma.hpp"

Enemy::Enemy(EnemyType type, int health, int speed, Texture &texture, bool *playing, Grid *grid, int x, int y) : Entity(health, speed, texture, playing, grid, x, y)
{
  switch(type)
  {
    case SLIME:
      this->attackMode = MELEE;
      this->preferredDistance = 10;
      this->coldWeapon = new Arma(3, 150, 6, this);
      this->semiWidth -= 3.7;
      this->semiHeight -= 5;
      break;
    case MONKEY:
      this->attackMode = RANGED;
      this->preferredDistance = 100;
      this->gun = new Arma(2, 200, 10, 3, 3, this);
      break;
  }
}

void Enemy::goTo(float targetX, float targetY, float time)
{
  float displacementX = targetX - this->x;
  float displacementY = targetY - this->y;
  float magnitude = sqrt(pow(displacementX, 2) + pow(displacementY, 2));
  if(magnitude > preferredDistance)
  {
    displacementX /= magnitude;
    displacementY /= magnitude;
    displacementX *= this->speed * time;
    displacementY *= this->speed * time;
    if(!this->collisionMap(this->x + displacementX, this->y + displacementY, NONE)) this->sprite.move(displacementX, displacementY);
  }
  else
  {
    if(this->attackMode == MELEE) this->coldWeapon->hit({}, this->grid->player, NONE);
    else this->gun->fire(Vector2f(targetX, targetY), Vector2f(this->x, this->y));
  }
  if(this->attackMode == MELEE) this->coldWeapon->update(time, {}, this->grid->player);
  else this->gun->update(time, {}, this->grid->player);
  this->updateXY(); 
  if(this->damaged > 0) this->damaged -= time;
  else this->sprite.setColor(Color::White);
}


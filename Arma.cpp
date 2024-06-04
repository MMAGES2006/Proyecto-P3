#include "Arma.hpp"

/*Arma::Arma(int damage, int cooldown, int municion, Texture &texture)
{
}
*/
Arma::Arma(int damage, int cooldown, int municion, float radius, float speed, Entity* owner)
{
  this->damage = damage;
  this->cooldown = cooldown;
  this->timer = 0;
  this->municion = municion;
  this->radius = radius;
  this->speed = speed;
  this->owner = owner;
}

Arma::Arma(int damage, int cooldown, float radius, Entity* owner)
{
  this->damage = damage;
  this->cooldown = cooldown;
  this->timer = 0;
  this->radius = radius;
  this->owner = owner;
}

void Arma::hit(vector<Enemy*> targets, Player* player, Direction direction)
{
  if(this->timer > 0) return;
  this->timer = this->cooldown;
  CircleShape circle;
  circle.setRadius(this->radius);
  float x = 0, y = 0;
  switch(direction)
  {
    case UP:
      y = -this->owner->semiHeight;
      break;
    case LEFT:
      x = -this->owner->semiWidth;
      break;
    case DOWN:
      y = this->owner->semiHeight;
      break;
    case RIGHT:
      x = this->owner->semiWidth;
      break;
    case NONE:
      
      break;
  }
  circle.setPosition(this->owner->x - this->owner->semiWidth + x, this->owner->y - this->owner->semiHeight + y);
  if(player == NULL)
  {
    for(int j = 0; j < targets.size(); j++)
    {
        if(this->collision(targets[j], circle)) targets[j]->health -= this->damage;      
    }
  }
  else
  {
    if(this->collision(player, circle)) player->health -= this->damage;  
  }
}

void Arma::fire(Vector2f targetPosition, Vector2f origin)
{
  if(this->timer > 0) return;
  this->timer = this->cooldown; 
  CircleShape sprite;
  Vector2f direction = targetPosition - origin;
  float magnitude = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
  direction /= magnitude;
  sprite.setRadius(this->radius);
  sprite.setFillColor(Color::White);
  sprite.setPosition(this->owner->x, this->owner->y);
  this->bullets.push_back({sprite, direction});
}

void Arma::update(float time, vector<Enemy*> targets, Player* player)
{
  if(this->timer > 0) this->timer -= time;
  for (int i = 0; i < this->bullets.size(); i++)
  {
    this->bullets[i].sprite.move(this->bullets[i].direction * this->speed * time);
    if(this->collisionMap(this->bullets[i].sprite)) this->bullets.erase(this->bullets.begin()+i);
    if(player == NULL)
    {
       for(int j = 0; j < targets.size(); j++)
       {
          if(this->collision(targets[j], this->bullets[i].sprite)) 
          {
            targets[j]->health -= this->damage;
            this->bullets.erase(this->bullets.begin()+i); //idea, hacer tres tipos, este, que todos los enemigos que toque mueran, y que los 
            break;
          }      
       }
    }
    else
    {
      if(this->collision(player, this->bullets[i].sprite)) 
      {
        player->health -= this->damage;
        this->bullets.erase(this->bullets.begin()+i); //idea, hacer tres tipos, este, que todos los enemigos que toque mueran, y que los 
        break;
      }      
    }
  }
}

 void Arma::drawTo(RenderWindow &window)
 {
   for(int i = 0; i < this->bullets.size(); i++)  window.draw(this->bullets[i].sprite);
 }

 bool Arma::collision(Entity* target, CircleShape &circle)
 {
   FloatRect hitbox(target->x-target->semiWidth, target->y-target->semiHeight, target->semiWidth * 2, target->semiHeight * 2);
   return circle.getGlobalBounds().intersects(hitbox);
 }

 bool Arma::collisionMap(CircleShape &bullet)
 {
   float x = bullet.getPosition().x + this->radius;
   float y = bullet.getPosition().y + this->radius;
   if(x < 0 || x > this->owner->grid->pixel * this->owner->grid->cols || y < 0 || y > this->owner->grid->pixel * this->owner->grid->rows) return 1;
   if(this->owner->grid->identifyMap(x, y) > 0) return 1;
   return 0;
 }
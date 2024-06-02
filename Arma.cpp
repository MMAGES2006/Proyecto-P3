#include "Arma.hpp"

Arma::Arma(int damage, int cooldown, int municion, Texture &texture)
{
}

Arma::Arma(int damage, int cooldown, int municion, float bulletRadius, float maxSpeed, Entity* owner)
{
  this->damage = damage;
  this->cooldown = cooldown;
  this->timer = 0;
  this->municion = municion;
  this->bulletRadius = bulletRadius;
  this->maxSpeed = maxSpeed;
  this->owner = owner;
}


Arma::Arma(float radius) : currVelocity(0.f, 0.f), maxSpeed(15.f)
{
    this->bullet.setRadius(radius);
    this->bullet.setFillColor(Color::White);
    // this->semiWidth=this->sprite.getGlobalBounds().getSize().x/2;
    // this->semiHeight=this->sprite.getGlobalBounds().getSize().y/2;
    // this->sprite.setTexture(texture);
    // this->sprite.setTextureRect(IntRect(0, 0, 500, 500));
    // this->sprite.setScale(0.3, 0.35);
}

void Arma::atacar()
{
}

void Arma::fire(RenderWindow  &window)
{
  if(this->timer > 0) return;
  this->timer = this->cooldown; 
  CircleShape sprite;
  Vector2f ownerPosition = *this->owner->playing ? Vector2f(900, 500) : Vector2f(this->owner->x, this->owner->y);
  Vector2f mousePosition = Vector2f(Mouse::getPosition(window));
  Vector2f direction = mousePosition - ownerPosition;
  float magnitude = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
  direction /= magnitude;
  sprite.setRadius(this->bulletRadius);
  sprite.setFillColor(Color::White);
  sprite.setPosition(this->owner->x, this->owner->y);
  bullets.push_back({sprite, direction});
}

void Arma::update(float time)
{
  if(this->timer > 0) this->timer -= time;
  for (int i = 0; i < bullets.size(); i++)
  {
    bullets[i].sprite.move(bullets[i].direction * this->maxSpeed * time);
    if (bullets[i].sprite.getPosition().x < 0 || bullets[i].sprite.getPosition().x > 1800 || bullets[i].sprite.getPosition().y < 0 || bullets[i].sprite.getPosition().y > 1000)
      bullets.erase(bullets.begin()+i);
  }
}

 void Arma::drawTo(RenderWindow &window)
 {
   for (int i = 0; i < bullets.size(); i++)  window.draw(bullets[i].sprite);
 }
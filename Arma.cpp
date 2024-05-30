#include "Arma.hpp"

Arma::Arma(int damage, int cooldown, int municion, Texture &texture)
{
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

void Arma::disparar()
{
}

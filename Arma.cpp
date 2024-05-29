#include "Arma.hpp"

Arma::Arma(int damage, int cooldown, int municion, Texture &texture)
{
}

Arma::Arma(float radius) : currVelocity(0.f, 0.f), maxSpeed(15.f)
{
    this->bullet.setRadius(radius);
    this->bullet.setFillColor(Color::White);
}

void Arma::atacar()
{
}

void Arma::disparar()
{
}

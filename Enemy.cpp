#include "Enemy.hpp"
#include "Player.hpp"

Enemy::Enemy(int health, int speed, Texture &texture, bool *playing, Grid *grid, int x, int y) : Entity(health, speed, texture, playing, grid, x, y)
{
}

void Enemy::seguirJugador()
{
}
#include "Enemy.hpp"
#include "Player.hpp"

Enemy::Enemy(int health, int speed, Texture &texture, bool *playing, Grid *grid, int x, int y) : Entity(health, speed, texture, playing, grid, x, y) {}

void Enemy::seguirJugador()
{
    xPos = zombieSprite.getPosition().x;
    yPos = zombieSprite.getPosition().y;

    zombiePosition = sf::Vector2f(xPos, yPos);

    playerPosition = player.GetPosition();

    // Incorrectly outputs player position
    // This outputs 0 constantly. But why?
    std::cout << "X: " << player.playerPosition.x << " Y: " << player.playerPosition.y << std::endl;

    direction = playerPosition - zombiePosition;
    normalizedDir = direction / sqrt(pow(direction.x, 2) + pow(direction.y, 2));

    speed = 2;

    // Rotate the Zombie relative to player position
    const float PI = 3.14159265;

    float dx = zombiePosition.x - playerPosition.x;
    float dy = zombiePosition.y - playerPosition.y;

    float rotation = (atan2(dy, dx)) * 180 / PI;

    zombieSprite.setRotation(rotation + 45);

    sf::Vector2f currentSpeed = normalizedDir * speed;

    zombieSprite.move(currentSpeed);
}
#include "Player.hpp"
#include "Arma.hpp"
#include "Menu.hpp"

Player::Player(int health, int speed, Texture &texture, bool* playing, Grid* grid, int x, int y): 
Entity(health, speed, texture, playing, grid, x, y)
{
  this->weapon = 1;
  this->wait = 0;
  this->direction = NONE;
  this->coldWeapon = new Arma(10, 20, 15, this);
  this->gun = new Arma(5, 50, 10, 3, 3, this);
  this->grid->player = this;

}
void Player::control(RenderWindow &window, float time)
{
  float displacement = this->speed * time;
  this->updateXY();
  this->updateRoom();
  if(Keyboard::isKeyPressed(Keyboard::W)) 
  {
    direction = UP;
    if(!this->collisionMap(this->x, this->y - displacement, UP)) sprite.move(0, -displacement);
  }
  if(Keyboard::isKeyPressed(Keyboard::A))
  {
    direction = LEFT;
    if(!this->collisionMap(this->x - displacement, this->y, LEFT)) sprite.move(-displacement, 0);
  }
  if(Keyboard::isKeyPressed(Keyboard::S))
  {
    direction = DOWN;
    if(!this->collisionMap(this->x, this->y + displacement, DOWN)) sprite.move(0, displacement);
  }
  if(Keyboard::isKeyPressed(Keyboard::D)) 
  {
    direction = RIGHT;
    if(!this->collisionMap(this->x + displacement, this->y, RIGHT)) sprite.move(displacement, 0);
  }
  if(Mouse::isButtonPressed(Mouse::Right) && (this->wait <= 0)) 
  {
    this->wait = 25;
    this->weapon *= -1;
  }
  if(Mouse::isButtonPressed(Mouse::Left)) 
  {
    if(this->weapon > 0)
    {
        if(*(this->playing)) this->gun->fire(Vector2f(Mouse::getPosition(window)), Vector2f(900, 500));
        else this->gun->fire(Vector2f(Mouse::getPosition(window)), Vector2f(this->x, this->y)); 
    }
    else this->coldWeapon->hit(this->grid->activeRoom->enemies, NULL, direction);
  }
  this->gun->update(time, this->grid->activeRoom->enemies, NULL); 
  this->coldWeapon->update(time, this->grid->activeRoom->enemies, NULL);
  if(this->wait > 0) this->wait -= time;
}

void Player::updateRoom()
{
  this->grid->newRoom.first = (4 * this->x) / (this->grid->pixel * this->grid->cols);
  this->grid->newRoom.second = (4* this->y) / (this->grid->pixel * this->grid->rows);
}

void Player::pickUpItem(const Item& item) {
    inventory.addItem(item);
}

sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}

void Player::showInventory() const {
    inventory.listItems();
}
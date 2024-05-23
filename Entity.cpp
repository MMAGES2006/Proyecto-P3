#include "Entity.hpp"

Entity::Entity(int health, int speed, int skin, Grid* grid, int x, int y)
{
    string skinName;
    Texture texture;
    this->health = health;
    this->speed = speed;
    this->grid = grid;
    switch(skin)
    {
        case monkey:
            skinName="sprites/P1.png";
            break;
    }
    if (!texture.loadFromFile(skinName)) cout << "Error al cargar imagen" << '\n';
    this->sprite.setTexture(texture);
    this->sprite.setTextureRect(IntRect(0, 0, 248, 243));
    this->sprite.setScale(0.3, 0.35);
    this->sprite.setPosition(x, y);
    this->semiWidth=this->sprite.getGlobalBounds().getSize().x/2;
    this->semiHeight=this->sprite.getGlobalBounds().getSize().y/2;
}

void Entity::drawTo(RenderWindow &window)
{
    window.draw(this->sprite);
}

void Entity::update()
{
  return;
}

bool Entity::collisionMap(float x, float y) //esta así para que sea más rápido, bueno, al menos creo que así es más rapido
{
  /*
  if(identifyCoordinates(x-semiWidth, y)<1)
  {
    if(identifyCoordinates(x+semiWidth, y)<1)
    {
        if(identifyCoordinates(x, y+semiHeight)<1)
        {
            if(identifyCoordinates(x-semiWidth, y+semiHeight)<1)
            {
                if(identifyCoordinates(x+semiWidth, y+semiHeight)<1)
                {
                    if(identifyCoordinates(x, y)) return 0;
                }
            }
        }
    }
  }
  return 1;
  */
  if(identifyCoordinates(x, y)>0) return 1;
  else return 0;
}

int Entity::identifyCoordinates(float x, float y)
{
  int indexX = x / this->grid->pixel;
  int indexY = y / this->grid->pixel;
  return this->grid->map[indexX][indexY];
}
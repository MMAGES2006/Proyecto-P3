#include "Room.hpp"
#include "Grid.hpp"
#include "Enemy.hpp"

Room::Room(RoomType type, int x, int y, Grid* grid)
{
vector<vector<int>> spawnGrid = vector<vector<int>>(45, vector<int>(25, -1));
vector<vector<int>> combat1Grid = vector<vector<int>>(45, vector<int>(25, -2));
vector<vector<int>> combat2Grid = {{0}};
vector<vector<int>> combat3Grid = {{0}};
vector<vector<int>> special1Grid = vector<vector<int>>(45, vector<int>(25, -3));
vector<vector<int>> special2Grid = {{0}};
vector<vector<int>> special3Grid = {{0}};
vector<vector<int>> exitGrid = vector<vector<int>>(45, vector<int>(25, -4));
  this->type = type;
  this->grid = grid;
  this->x = x;
  this->y = y;
  this->cornerX = x * this->grid->cols / 4;
  this->cornerY = y * this->grid->rows / 4;
  this->centerX = this->cornerX + (this->grid->cols / 8);
  this->centerY = this->cornerY + (this->grid->rows / 8);
  this->visited = 0;
  switch(type)
  {
    case SPAWN:
    {
      this->design = spawnGrid;
      
      break;
    }
    case COMBAT:
      this->design = combat1Grid;
      break;
    case SPECIAL:
      this->design = special1Grid;
      break;
    case EXIT:
      this->design = exitGrid;
      break;
  }
}

void Room::start()
{
  if(this->visited) return;
    //this->grid->map[this->centerX][this->centerY] = 1;
  switch(type)
  {
    case SPAWN:
      
      
      break;
    case COMBAT:
      {
        int slimes = rand() % 5 + 5;
        int spawnX;
        int spawnY;
        for(int i = 0; i < slimes; i++)
        {
          spawnX = cornerX + (rand() % (this->grid->cols / 4));
          spawnY = cornerY + (rand() % (this->grid->rows / 4));
          this->enemies.push_back(new Enemy(5, 3, this->grid->textures[1], this->grid->playing, this->grid, spawnX, spawnY));
        }
        //Enemy* entity = new Enemy(5, 3, this->grid->textures[1], this->grid->playing, this->grid, this->centerX, this->centerY);
        //this->entities.push_back(entity);
        break;
      }
    case SPECIAL:
      
      break;
    case EXIT:
      
      break;
  }
  this->visited = 1;
}


void Room::update(float playerX, float playerY, float time)
{
  if(this->type == COMBAT)
  {
    for(int i = 0; i < this->enemies.size(); i++)
    {
      this->enemies[i]->goTo(playerX, playerY, time);
    }
  }
}


void Room::drawTo(RenderWindow &window)
{
  if(this->type == COMBAT)
  {
    for(int i = 0; i < this->enemies.size(); i++)
      this->enemies[i]->drawTo(window);
  }
}
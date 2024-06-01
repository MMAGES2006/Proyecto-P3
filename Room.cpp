#include "Room.hpp"
#include "Grid.hpp"
#include "Entity.hpp"

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
  this->centerX = (x * this->grid->cols / 4) + (this->grid->cols / 8);
  this->centerY = (y * this->grid->rows / 4) + (this->grid->rows / 8);
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
  if(!this->visited)
  {
    //this->grid->map[this->centerX][this->centerY] = 1;
    if(this->type == COMBAT)
    {
      Entity* entity = new Entity(5, 3, this->grid->textures[1], this->grid->playing, this->grid, this->centerX, this->centerY);
      this->entities.push_back(entity);
    }
  }
}

void Room::update(RenderWindow &window)
{
  if(this->type == COMBAT)
  {
    for(int i = 0; i < this->entities.size(); i++)
    {
      this->entities[i]->drawTo(window);
    }
  }
}
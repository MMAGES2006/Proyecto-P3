#include "Room.hpp"
#include "Grid.hpp"

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
  this->x = x;
  this->y = y;
  this->grid = grid;
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
  if(this->type == COMBAT)
  {
    this->grid->map[this->x][this->y] = 1;
  }
}
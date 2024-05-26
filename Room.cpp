#include "Room.hpp"

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
  switch(type)
  {
    case SPAWN:
    {
      this->roomGrid = spawnGrid;
      this->x = x + 22;
      this->y = y + 12;
      break;
    }
    case COMBAT:
      this->roomGrid = combat1Grid;
      break;
    case SPECIAL:
      this->roomGrid = special1Grid;
      break;
    case EXIT:
      this->roomGrid = exitGrid;
      break;
  }
}
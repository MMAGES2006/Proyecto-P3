#include "Grid.hpp"
#include "Player.hpp"

Grid::Grid(int cols, int rows, int pixel, float changeFactor, bool* playing, vector<Texture> &textures)
{
  this->cols = cols;
  this->rows = rows;
  this->pixel = pixel;
  this->changeFactor = changeFactor;
  this->playing = playing;
  this->textures = textures;
  for(int i=0; i<4; i++)
  {
    for(int j=0; j<4; j++) this->miniMap[i][j] = NULL;
  }
  this->map = vector<vector<int>>(cols, vector<int>(rows, 0));
  this->generateMap();
}

void Grid::generateMap()
{  
  //mainPath
  int mainCombatRooms = 4 + ((rand() % 4)/3);
  int chosenNeighbor;
  int numberNeighbor;
  RoomType fakeMap[4][4];

  int x = rand() % 4, y = rand() % 4;

  this->createRoom(x, y, SPAWN);
  this->activeRoom = this->miniMap[x][y];
  this->spawnX = this->miniMap[x][y]->centerX;
  this->spawnY = this->miniMap[x][y]->centerY;
  

  vector<pair<int,int>> neighbors;
  
  for(int leftMainPath = mainCombatRooms + 1; leftMainPath > 0; leftMainPath--)
  {
    for(int i=0; i<4; i++)
    {
      for(int j=0; j<4; j++)
      {
        if(this->miniMap[i][j]) fakeMap[i][j] = this->miniMap[i][j]->type;
        else fakeMap[i][j] = VOID;
      }
    }
    if(this->enoughLenght(x, y-1, leftMainPath, fakeMap)) neighbors.push_back({x, y-1});
    if(this->enoughLenght(x-1, y, leftMainPath, fakeMap)) neighbors.push_back({x-1, y});
    if(this->enoughLenght(x+1, y, leftMainPath, fakeMap)) neighbors.push_back({x+1, y});
    if(this->enoughLenght(x, y+1, leftMainPath, fakeMap)) neighbors.push_back({x, y+1});

    numberNeighbor = neighbors.size();
    chosenNeighbor = rand() % numberNeighbor;
    x = neighbors[chosenNeighbor].first;
    y = neighbors[chosenNeighbor].second;
    if(leftMainPath > 1) this->createRoom(x, y, COMBAT);
    else this->createRoom(x, y, EXIT);
    neighbors.clear();
  }
  
  //deviations
  RoomType chosenType = SPECIAL;
  int extraSpecial = 3;
  int increased = 1;
  int extraCombat = 3;
  int finish = 0;
  int a;
  while(chosenType!=VOID)
  {
    this->generateExtra(chosenType);
    a = rand() % (extraSpecial * increased + extraCombat + finish); 
    if(a < extraSpecial * increased) 
    {
      chosenType = SPECIAL;
      extraSpecial--;
      finish += increased;
    }
    else if(a < extraSpecial * increased + extraCombat) 
    {
      chosenType = COMBAT;
      extraCombat--;
      finish ++;
    }
    else chosenType = VOID;
  }  
  //this->createRoom(0, 0, COMBAT);
}

void Grid::drawTo(RenderWindow &window)
{
  for (int i = 0; i < this->cols; i++)
  {
    for (int j = 0; j < this->rows; j++)
    {
        if(this->map[i][j])
        {
            RectangleShape rect(Vector2f(this->pixel, this->pixel));
            rect.setPosition(Vector2f(i * this->pixel, j * this->pixel));
        switch(this->map[i][j])
        {
            case -1:
            rect.setFillColor(Color::Green);
            break;
            case -2:
            rect.setFillColor(Color::Red);
            break;
            case -3:
            rect.setFillColor(Color::Yellow);
            break;
            case -4:
            rect.setFillColor(Color::Magenta);
            break;
            case -5:
            rect.setFillColor(Color::Blue);
            break;
        }
        window.draw(rect);
        }
    }
  }
  if((this->activeRoom->x != this->newRoom.first) || (this->activeRoom->y != this->newRoom.second))
  {
    if(this->miniMap[this->newRoom.first][this->newRoom.second])
    {
      this->activeRoom = this->miniMap[this->newRoom.first][this->newRoom.second];
      this->activeRoom->start();
    }
  }
}

int Grid::identifyMap(float x, float y)
{
  int indexX = x / this->pixel;
  int indexY = y / this->pixel;
  return this->map[indexX][indexY];
}

void Grid::toggle(int x, int y)
{   
  int indexX = x / this->pixel;
  int indexY = y / this->pixel;
  //this->map[indexX][indexY] = (this->map[indexX][indexY] < 1) ? 1 : 0;
  this->map[indexX][indexY]++;
  if(this->map[indexX][indexY] == 2) this->map[indexX][indexY] = -4;
}

void Grid::generateExtra(RoomType type)
{
  int x;
  int y;
  int chosenNeighbor;
  int numberNeighbor;
  int evaluationMap[4][4];
  vector<pair<int,int>> neighbors;

  for(int i=0; i<4; i++)
  {
    for(int j=0; j<4; j++) evaluationMap[i][j] = 0;
  }

  if(type == SPECIAL)
  {
    for(int i=0; i<4; i++)
    {
      for(int j=0; j<4; j++)
      {
        if(this->miniMap[i][j])
        { 
          if(this->potentialRoom(i, j-1)) evaluationMap[i][j-1] = 1;
          if(this->potentialRoom(i-1, j)) evaluationMap[i-1][j] = 1;
          if(this->potentialRoom(i+1, j)) evaluationMap[i+1][j] = 1;
          if(this->potentialRoom(i, j+1)) evaluationMap[i][j+1] = 1;
        }
      }
    }    
  }
  else
  {
    for(int i=0; i<4; i++)
    {
      for(int j=0; j<4; j++)
      {
        if(this->miniMap[i][j])
        { 
          if(this->miniMap[i][j]->type != SPECIAL)
          {
            if(this->potentialRoom(i, j-1)) evaluationMap[i][j-1] = 1;
            if(this->potentialRoom(i-1, j)) evaluationMap[i-1][j] = 1;
            if(this->potentialRoom(i+1, j)) evaluationMap[i+1][j] = 1;
            if(this->potentialRoom(i, j+1)) evaluationMap[i][j+1] = 1;
          }
        }
      }
    }
  }
  
  for(int i=0; i<4; i++)
  {
    for(int j=0; j<4; j++)
    {
      if(evaluationMap[i][j] == 1) neighbors.push_back({i, j});
    }
  }
  
  numberNeighbor = neighbors.size();

  if(numberNeighbor == 0) return;
  chosenNeighbor = rand() % numberNeighbor;
  x = neighbors[chosenNeighbor].first;
  y = neighbors[chosenNeighbor].second;
  this->createRoom(x, y, type);
}

void Grid::createRoom(int x, int y, RoomType type)
{
  int cellWidth = this->cols / 4;
  int cellHeight = this->rows / 4;
  int positionX = cellWidth * x; 
  int positionY = cellHeight * y;
  Room* room = new Room(type, x, y, this);
  this->miniMap[x][y] = room;
  for(int i = 0; i < cellWidth; i++)
  {
    for(int j = 0; j < cellHeight; j++) this->map[i + positionX][j + positionY] = room->design[i][j];
  }
}

bool Grid::enoughLenght(int x, int y, int lenght, RoomType fakeMap[4][4])
{
  if((x < 0) || (y < 0) || (x > 3) || (y > 3)) return 0;
  if(fakeMap[x][y]!=VOID) return 0;
  if(lenght > 1)
  {
    fakeMap[x][y] = COMBAT;
    lenght--;
    bool answer = (enoughLenght(x, y-1, lenght, fakeMap) || enoughLenght(x-1, y, lenght, fakeMap) || enoughLenght(x+1, y, lenght, fakeMap) || enoughLenght(x, y+1, lenght, fakeMap));
    return answer;
  }
  else return 1;
}

bool Grid::potentialRoom(int x, int y)
{
  if((x < 0) || (y < 0) || (x > 3) || (y > 3)) return 0;
  if(this->miniMap[x][y]) return 0;
  return 1;
}

Grid::~Grid()
{
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; j++) delete this->miniMap[i][j];
  }
}
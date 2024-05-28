#include "Grid.hpp"

Grid::Grid(int cols, int rows, int pixel, float changeFactor, bool* playing)
{
  this->cols = cols;
  this->rows = rows;
  this->pixel = pixel;
  this->changeFactor = changeFactor;
  this->playing = playing;
  for(int i=0; i<4; i++)
  {
    for(int j=0; j<4; j++) this->roomsMatrix[i][j] = NULL;
  }
  for(int i=0; i<4; i++)
  {
    this->miniMap.push_back({});
    for(int j=0; j<4; j++) this->miniMap[i].push_back(VOID);
  }
  this->map = vector<vector<int>>(cols, vector<int>(rows, 0));
  this->generateMap();
  /*for (int i = 0; i < cols; i++)
  {
    map.push_back({});
    for (int j = 0; j < rows; j++) map[i].push_back(0);
  }*/
}

void Grid::generateMap()
{
  srand(time(0));
  bool incomplete = 1;
  int mainCombatRooms = 3 + (rand() % 4)/3;
  cout<<mainCombatRooms<<'\n';
  int chosenNeighbor;
  int numberNeighbor;
  vector<vector<RoomType>> fakeMap;
  for(int i=0; i<4; i++)
  {
    fakeMap.push_back({});
    for(int j=0; j<4; j++) fakeMap[i].push_back(VOID);
  }
  /*int extraSpecialRooms = rand() % 3;
  cout<<extraSpecialRooms<<'\n';
  int chosenNeighbor;
  int numberNeighbor;*/

  int x = rand() % 4, y = rand() % 4;
  int x1, y1;

  cout<<"spawn\n";
  this->createRoom(x, y, SPAWN);
  cout<<'\n';
  
  this->spawnX = this->roomsMatrix[x][y]->x * this->pixel;
  this->spawnY = this->roomsMatrix[x][y]->y * this->pixel;

  vector<pair<int,int>> neighbors;

  for(int leftMainPath = mainCombatRooms + 1; leftMainPath > 0; leftMainPath--)
  {
    for(int i=0; i<4; i++)
  {
    for(int j=0; j<4; j++) cout<<this->miniMap[i][j];
    cout<<' ';
  }
    fakeMap = this->miniMap;
    cout<<"a\n";
    if(this->enoughLenght(x, y-1, leftMainPath, fakeMap)) neighbors.push_back({x, y-1});
    cout<<"b\n";
    if(this->enoughLenght(x-1, y, leftMainPath, fakeMap)) neighbors.push_back({x-1, y});
    cout<<"c\n";
    if(this->enoughLenght(x+1, y, leftMainPath, fakeMap)) neighbors.push_back({x+1, y});
    cout<<"d\n";
    if(this->enoughLenght(x, y+1, leftMainPath, fakeMap)) neighbors.push_back({x, y+1});
    for(int i=0; i<neighbors.size(); i++) cout<<neighbors[i].first<<','<<neighbors[i].second<<'\n';
    cout<<'\n';
    for(int i=0; i<4; i++)
  {
    for(int j=0; j<4; j++) cout<<this->miniMap[i][j];
    cout<<' ';
  }
    numberNeighbor = neighbors.size();
    chosenNeighbor = rand() % numberNeighbor;
    x = neighbors[chosenNeighbor].first;
    y = neighbors[chosenNeighbor].second;
    if(leftMainPath > 1) 
    {
      cout<<"requiredCombat\n";
      this->createRoom(x, y, COMBAT);
      cout<<'\n';
    }
    else
    {
      cout<<"exit\n";
      this->createRoom(x, y, EXIT);
      cout<<'\n';
    }
    neighbors.clear();
  }
  /*
  while(incomplete)
  {
    if(this->potentialRoom(x, y-1)) neighbors.push_back({x, y-1});
    if(this->potentialRoom(x-1, y)) neighbors.push_back({x-1, y});
    if(this->potentialRoom(x+1, y)) neighbors.push_back({x+1, y});
    if(this->potentialRoom(x, y+1)) neighbors.push_back({x, y+1});
    for(int i=0; i<neighbors.size(); i++) cout<<neighbors[i].first<<','<<neighbors[i].second<<'\n';
    cout<<'\n';
    numberNeighbor = neighbors.size();
    chosenNeighbor = rand() % numberNeighbor;
    x = neighbors[chosenNeighbor].first;
    y = neighbors[chosenNeighbor].second;
    if(requiredCombatRooms > 0)
    {
      cout<<"requiredCombat\n";
      this->createRoom(x, y, COMBAT);
      cout<<'\n';
      requiredCombatRooms--;
      numberNeighbor--;
      if(numberNeighbor > 0)
      {
        neighbors.erase(neighbors.begin() + chosenNeighbor);
        chosenNeighbor = rand() % numberNeighbor;
        x1 = neighbors[chosenNeighbor].first;
        y1 = neighbors[chosenNeighbor].second;
        if(requiredSpecialRooms > 0)
        {
            cout<<"requiredSpecial\n";
            this->createRoom(x1, y1, SPECIAL);
            cout<<'\n';
            requiredSpecialRooms--;
        }
        else if(extraCombatRooms + extraSpecialRooms > 0)
        {
            if((rand() % (extraCombatRooms + extraSpecialRooms)) < extraCombatRooms)
            {
                cout<<"extraCombat\n";
                this->createRoom(x1, y1, COMBAT);
                cout<<'\n';
                extraCombatRooms--;
            }
            else
            {
                cout<<"extraSpecial\n";
                this->createRoom(x1, y1, SPECIAL);
                cout<<'\n';
                extraSpecialRooms--;
            }
        }
      }
      neighbors.clear();
    }
    else
    {
      cout<<"exit"<<'\n';
      this->createRoom(x, y, EXIT);
      cout<<'\n';
      incomplete = 0;
      numberNeighbor--;
      if(numberNeighbor > 0)
      {
        neighbors.erase(neighbors.begin() + chosenNeighbor);
        chosenNeighbor = rand() % numberNeighbor;
        x1 = neighbors[chosenNeighbor].first;
        y1 = neighbors[chosenNeighbor].second;
        if(extraCombatRooms + extraSpecialRooms > 0)
        {
            if((rand() % (extraCombatRooms + extraSpecialRooms)) < extraCombatRooms)
            {
                cout<<"extraCombat\n";
                this->createRoom(x1, y1, COMBAT);
                cout<<'\n';
                extraCombatRooms--;
            }
            else
            {
                cout<<"extraSpecial\n";
                this->createRoom(x1, y1, SPECIAL);
                cout<<'\n';
                extraSpecialRooms--;
            }
        }
      }
      cout<<"completed\n";
    }
  }
  */
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
        }
        window.draw(rect);
        }
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
  this->map[indexX][indexY] = (this->map[indexX][indexY] < 1) ? 1 : 0;
}

void Grid::createRoom(int x, int y, RoomType type)
{
  int positionX = (this->cols*x) / 4; 
  int positionY = (this->rows*y) / 4;
  cout<<"position: ("<<positionX<<','<<positionY<<")\n";
  int cellWidth = this->cols / 4;
  int cellHeight = this->rows / 4;
  cout<<"proportions: "<<cellWidth<<','<<cellHeight<<'\n';
  Room room(type, positionX, positionY, this);
  this->roomsMatrix[x][y] = &room;
  this->miniMap[x][y] = type;
  if(this->roomsMatrix[x][y]!=NULL) cout<<"room is going to be created";
  else cout<<"room failed";
  cout<<'\n';
  for(int i = 0; i < cellWidth; i++)
  {
    for(int j = 0; j < cellHeight; j++) this->map[i + positionX][j + positionY] = room.roomGrid[i][j];
  }
  cout<<"room actually created\n";
}

bool Grid::enoughLenght(int x, int y, int lenght, vector<vector<RoomType>> fakeMap)
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
  else if(this->roomsMatrix[x][y]!=NULL) return 0;
  cout<<'('<<x<<','<<y<<") was approved\n";
  return 1;
}
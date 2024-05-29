#ifndef Room_h
#define Room_h
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;

enum RoomType{SPAWN, COMBAT, SPECIAL, EXIT, VOID};
class Grid;

class Room
{
public:
    RoomType type;
    int subType;
    int x, y;
    int width, height;
    Grid* grid;
    vector<vector<int>> design;
    Room(RoomType type, int x, int y, Grid* grid); //constructor
};

#endif
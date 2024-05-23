#ifndef Grid_h
#define Grid_h
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;

class Grid
{
public:
    vector<vector<int>> map;
    vector<vector<int>> next;
    int cols, rows, pixel;
    Grid(int cols, int rows, int pixel);
    void drawTo(RenderWindow  &window);
    void update();
    void toggle(int x,int y);
    //int calcularVecinos(int i, int j);
};

#endif
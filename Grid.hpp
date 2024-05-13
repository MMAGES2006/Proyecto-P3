#ifndef Grid_h
#define Grid_h
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;

class Grid
{
private:
    vector<vector<int>> tablero;
    vector<vector<int>> siguiente;
    int rows, cols, w, h;

public:
    Grid(int n, int w, int h);
    Grid(int rows, int cols);

    void drawTo(RenderWindow  &window);
    void update();
    void toggle(int x,int y);
    int calcularVecinos(int i, int j);
};

#endif
#include "Grid.hpp"

Grid::Grid(int cols, int rows, int pixel)
{
    this->cols = cols;
    this->rows = rows;
    this->pixel = pixel;
    for (int i = 0; i < cols; i++)
    {
        map.push_back({});
        for (int j = 0; j < rows; j++)
        {
            map[i].push_back(0);
        }
    }
    this->next = vector<vector<int>>(rows, vector<int>(cols, 0));
}

void Grid::drawTo(RenderWindow &window)
{
    for (int i = 0; i < this->cols; i++)
    {
        for (int j = 0; j < this->rows; j++)
        {
            if (map[i][j])
            {
                RectangleShape rect(Vector2f(this->pixel, this->pixel));
                rect.setPosition(Vector2f(i * this->pixel, j * this->pixel));
                rect.setFillColor(Color::Blue);
                window.draw(rect);
            }
        }
    }
}

void Grid::toggle(int x, int y)
{   
    int indexX = x / this->pixel;
    int indexY = y / this->pixel;

    map[indexX][indexY] = (map[indexX][indexY] + 1) % 2;
}
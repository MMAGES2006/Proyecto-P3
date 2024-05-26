#ifndef Enemy_h
#define Enemy_h
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include <vector>
using namespace sf;
using namespace std;

class Enemy: public Entity
{
public:
<<<<<<< HEAD
    int health;
    float speed;
    float x, y;
    float semiWidth, semiHeight;
    bool* playing; //es un booleano que es verdadero si se esta jugando, falso sino
    vector<bool> hitbox;
    Grid* grid;
    Sprite sprite;
    void drawTo(RenderWindow  &window);
    void update(); 
    bool collisionMap(float x, float y, Direction direction); 
    void updateXY(); 
    Enemy(int health, int speed, Texture &texture, Grid* grid, int x, int y); //constructor
    void seguirPlayer(); 

=======
    Enemy(int health, int speed, Texture &texture, bool* playing, Grid* grid, int x, int y); //constructor
>>>>>>> 21d16b06ba17d8e1b4a5b285b56bab227f038f50
};

#endif
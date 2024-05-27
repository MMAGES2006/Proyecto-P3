#ifndef Arma_h
#define Arma_h
#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include <vector>
using namespace sf;
using namespace std;

class Arma
{
private:

public:
    int damage; 
    float cooldown; 

    Sprite sprite; 
    Arma(int damage, int cooldown, Texture &texture); 

    void atacar(); // para melee.
    void disparar(); //Armas de fuego.
    void efecto(); //Esta todavia no me decido si tendran efectos las armas, asi que queda por si acaso.
    
};

#endif
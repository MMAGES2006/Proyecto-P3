#ifndef Object_h
#define Object_h
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Grid.hpp"
#include "Player.hpp"
using namespace sf;
using namespace std;

enum ObjectTypes {DEFAULT = 0};

class Object
{
    public: 

    short unsigned type; 
    string calidad; 

    Object();
    ~Object(); 

    virtual Object* clone() = 0; 


}; 

#endif
#ifndef Inventory_h
#define Inventory_h
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Object.hpp"
using namespace sf;
using namespace std;

class Inventory : public Object
{
    private: 
    Object** pobject; 
    int numofObjects; 
    int maxObjects; 

    void iniciar();
    void nullify(const unsigned from = 0); 
    void clear();  

    public: 
    //vector<Object> inventario;
    Inventory(int maxObjects); 
    ~Inventory(); 

    const unsigned& size() const; 
    const unsigned& maxsize() const; 

    void limpiar(); 
    const bool vacio() const; 
    const bool add(Object* object); 
    const bool remove(const unsigned index); 

    const bool savetoFile(const string fileName); 
    const bool loadfromFile(const string fileName); 


}; 

#endif
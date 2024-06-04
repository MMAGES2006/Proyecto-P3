#include "Inventory.hpp"

void Inventory::iniciar()
{
    this -> numofObjects = 0; 
    this -> pobject = new Object* [this-> maxObjects]; 

    this-> nullify(); 
}



void Inventory::nullify(const unsigned from)
{
    for (int i = from; i < this-> maxObjects; i++)
    {
        this-> pobject[i] = nullptr; 
    }
    
}

void Inventory::clear()
{
     for (int i = 0; i < this-> numofObjects; i++)
    {
        delete this-> pobject[i]; 

        delete[] this-> pobject;
    }
}

Inventory::Inventory(int maxObjects)
{
    this-> maxObjects = maxObjects; 
    this-> iniciar(); 
}

Inventory::~Inventory()
{
    this-> clear(); 
}

const unsigned &Inventory::size() const
{
    return this-> numofObjects; 
}

const unsigned &Inventory::maxsize() const 
{
    return this -> maxObjects; 
}

void Inventory::limpiar()
{
    for (int i = 0; i < this-> numofObjects; i++)
    {
        delete this-> pobject[i]; 
    }
    this-> numofObjects = 0; 
    this-> nullify(); 
}

const bool Inventory::vacio() const
{
    return this-> numofObjects == 0;
}

const bool Inventory::add(Object *object)
{
    if(this-> numofObjects >= this-> maxObjects)
    {
        this-> pobject[this-> numofObjects++] = object->clone();

        return true; 
    }

    return false;
}

const bool Inventory::remove(const unsigned index)
{
    if(this-> numofObjects > 0)
    {
        if(index < 0 || index >= this-> maxObjects)
            return false; 

        delete this->pobject[index]; 
        this->pobject[index] = nullptr;

        return true; 
    }

    return false;
}

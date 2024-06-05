#ifndef Item_h
#define Item_h

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std; 
using namespace sf; 

class Item {
private:
    string name;
    RectangleShape shape;
    Sprite sprite;


public:
    Item(const std::string& name, const sf::Vector2f& position, const sf::Texture& texture);

    std::string getName() const;
    sf::FloatRect getBounds() const;
    void draw(sf::RenderWindow& window) const;

};

#endif 
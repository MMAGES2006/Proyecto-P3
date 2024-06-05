#ifndef Item_h
#define Item_h

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

class Item
{
private:
    Sprite sprite;
    string name;

public:
    vector<Item *> items;
    Item(const string &name, const Vector2f &position, const Texture &texture);
    string getName() const;

    FloatRect getBounds() const;

    void draw(sf::RenderWindow &window) const;
};

#endif
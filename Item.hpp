#ifndef Item_h
#define Item_h

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Player.hpp"

using namespace std;
using namespace sf;

class Item
{
private:
    Sprite sprite;
    string name;

public:
    vector<Item *> items;
    int curvida;
    Item(const string &name, const Vector2f &position, const Texture &texture, int curvida);
    string getName() const;

    FloatRect getBounds() const;

    void draw(sf::RenderWindow &window) const;

    void curar(int curvid, Player *player);
};

#endif
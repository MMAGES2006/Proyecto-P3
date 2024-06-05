#include "Item.hpp"

Item::Item(const string &name, const Vector2f &position, const Texture &texture, int curvid)
    : name(name), sprite(texture)
{
    sprite.setPosition(position);
}

std::string Item::getName() const
{
    return name;
}

FloatRect Item::getBounds() const
{
    return sprite.getGlobalBounds();
}

void Item::draw(sf::RenderWindow &window) const
{
    window.draw(sprite);
}

void Item::curar(int curvid, Player *player)
{
    player->health += curvid;
}
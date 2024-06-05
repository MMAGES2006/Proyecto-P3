#ifndef Inventario_h
#define Inventario_h 

#include <vector>
#include "Item.hpp"

class Inventory {
public:
    void addItem(const Item& item);
    void listItems() const;

private:
    std::vector<Item> items;
};

#endif // INVENTORY_HPP
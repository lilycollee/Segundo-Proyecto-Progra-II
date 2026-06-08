#ifndef PROYECTOIIPROGRAII_BACKPACK_H
#define PROYECTOIIPROGRAII_BACKPACK_H
#include <vector>
#include "Item.h"
class Backpack : public Item {
private:
    std::string name;
    std::vector<Item*> items;
public:
    Backpack();
    std::string getName() const override;
    void add(Item* item);
    std::string toString(int nivel) override;
    ~Backpack();
};


#endif //PROYECTOIIPROGRAII_BACKPACK_H
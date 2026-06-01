#ifndef PROYECTOIIPROGRAII_CONSUMABLE_H
#define PROYECTOIIPROGRAII_CONSUMABLE_H
#include <vector>
#include "Item.h"
class Consumable : public Item {
private:
    std::string name;
    std::vector<Item*> consumables;
public:
    Consumable();
    std::string getName() const override;
    void add(Item* element);
    std::string toString(int nivel) override;
};
#endif //PROYECTOIIPROGRAII_CONSUMABLE_H
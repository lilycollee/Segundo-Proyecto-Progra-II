#ifndef PROYECTOIIPROGRAII_WEAPON_H
#define PROYECTOIIPROGRAII_WEAPON_H
#include <string>
#include <vector>
#include "Item.h"
class Weapon : public Item {
private:
    std::string name;
    std::vector<Item*> weapons;
public:
    Weapon();
    std::string getName() const override;
    void add(Item* element);
    std::string toString(int nivel) override;
};
#endif //PROYECTOIIPROGRAII_WEAPON_H
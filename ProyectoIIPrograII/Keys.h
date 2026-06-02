#ifndef PROYECTOIIPROGRAII_KEYS_H
#define PROYECTOIIPROGRAII_KEYS_H
#include <vector>
#include "Item.h"
class Keys : public Item {
    std::string name;
    std::vector<Item*> keys;
public:
    Keys();
    std::string getName() const override;
    void add(Item* element);
    std::string toString(int nivel) override;
};
#endif //PROYECTOIIPROGRAII_KEYS_H
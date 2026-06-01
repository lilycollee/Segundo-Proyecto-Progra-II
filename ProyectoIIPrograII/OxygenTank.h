#ifndef PROYECTOIIPROGRAII_OXYGENTANK_H
#define PROYECTOIIPROGRAII_OXYGENTANK_H
#include "Item.h"
class OxygenTank : public Item {
private:
    std::string name;
    int capacity;
    bool active;
public:
    OxygenTank();
    std::string getName() const override;
    std::string description();
    bool getActive();
    void setActive(bool active);
    std::string toString(int nivel) override;
};
#endif //PROYECTOIIPROGRAII_OXYGENTANK_H
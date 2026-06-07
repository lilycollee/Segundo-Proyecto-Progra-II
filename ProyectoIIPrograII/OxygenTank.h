#ifndef PROYECTOIIPROGRAII_OXYGENTANK_H
#define PROYECTOIIPROGRAII_OXYGENTANK_H
#include "Item.h"
class OxygenTank : public Item {
private:
    std::string name;
    int capacity;
    bool active;
public:
    OxygenTank(std::string name, double capacity);
    std::string getName() const override;
    std::string description();
    bool getActive() const;
    void setActive(bool active);
    int getCapacity() const;
    void setCapacity(int capacity);
    std::string toString(int nivel) override;
};
#endif //PROYECTOIIPROGRAII_OXYGENTANK_H
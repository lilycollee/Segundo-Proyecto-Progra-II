#ifndef PROYECTOIIPROGRAII_LASERGUN_H
#define PROYECTOIIPROGRAII_LASERGUN_H
#include "Item.h"
class LaserGun : public Item {
private:
    std::string name;
public:
    LaserGun(std::string name);
    std::string getName() const override;
    std::string description();
    std::string toString(int nivel) override;
};
#endif //PROYECTOIIPROGRAII_LASERGUN_H
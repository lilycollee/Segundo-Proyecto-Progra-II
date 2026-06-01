#ifndef PROYECTOIIPROGRAII_DEACTIVATIONKEY_H
#define PROYECTOIIPROGRAII_DEACTIVATIONKEY_H
#include "Item.h"
class DeactivationKey : public Item {
private:
    std::string name;
public:
    DeactivationKey();
    std::string getName() const override;
    std::string description();
    std::string toString(int nivel) override;
};
#endif //PROYECTOIIPROGRAII_DEACTIVATIONKEY_H
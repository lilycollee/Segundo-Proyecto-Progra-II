#ifndef PROYECTOIIPROGRAII_MEDICALEQUIPMENT_H
#define PROYECTOIIPROGRAII_MEDICALEQUIPMENT_H
#include "Item.h"
class MedicalEquipment : public Item {
private:
    std::string name;
    int capacity;
    bool active;
public:
    MedicalEquipment();
    std::string getName() const override;
    std::string description();
    bool getActive();
    void setActive(bool active);
    std::string toString(int nivel) override;
};
#endif //PROYECTOIIPROGRAII_MEDICALEQUIPMENT_H
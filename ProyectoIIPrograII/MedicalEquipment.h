#ifndef PROYECTOIIPROGRAII_MEDICALEQUIPMENT_H
#define PROYECTOIIPROGRAII_MEDICALEQUIPMENT_H
#include "Item.h"
class MedicalEquipment : public Item {
private:
    std::string name;
    int capacity;
    bool active;
public:
    MedicalEquipment(std::string name, double capacity);
    std::string getName() const override;
    std::string description();
    bool getActive() const;
    void setActive(bool active);
    int getCapacity() const;
    void setCapacity(int capacity);
    std::string toString(int nivel) override;
};
#endif //PROYECTOIIPROGRAII_MEDICALEQUIPMENT_H
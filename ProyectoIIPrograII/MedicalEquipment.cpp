#include "MedicalEquipment.h"
#include <sstream>
MedicalEquipment::MedicalEquipment(std::string name, double capacity) {
    this->name = name;
    this->capacity = capacity;
    active = true;
}
std::string MedicalEquipment::getName() const {
    return name;
}
std::string MedicalEquipment::description() {
    std::stringstream s;
    s << "DESCRIPTION: " << name << " |Capacity: " << capacity << " |Used: " << (active ? "NO" : "YES") << "\n";
    return s.str();
}
bool MedicalEquipment::getActive() const {
    return active;
}
void MedicalEquipment::setActive(bool active) {
    this->active = active;
}
int MedicalEquipment::getCapacity() const {
    return capacity;
}
void MedicalEquipment::setCapacity(int capacity) {
    this->capacity = capacity;
}
std::string MedicalEquipment::toString(int nivel = 0) {
    std::stringstream s;
    s << std::string(nivel * 3, ' ') << "[MEDICAL EQUIPMENT]\n";
    s << "|" << std::string(nivel * 4, ' ') << description();
    return s.str();
}

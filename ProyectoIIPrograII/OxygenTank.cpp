#include "OxygenTank.h"
#include <sstream>

OxygenTank::OxygenTank() {
    name = "Oxygen Capsule Replacement";
    capacity = 40;
    active = true;
}
std::string OxygenTank::getName() const {
    return name;
}
std::string OxygenTank::description() {
    std::stringstream s;
    s << "DESCRIPTION: " << name << " |Capacity: " << capacity << " |Used: " << (active ? "NO" : "YES") << "\n";
    return s.str();
}
bool OxygenTank::getActive() {
    return active;
}
void OxygenTank::setActive(bool active) {
    this->active = active;
}
std::string OxygenTank::toString(int nivel = 0) {
    std::stringstream s;
    s << std::string(nivel * 3, ' ') << "[OXYGEN TANK]\n";
    s << "|" << std::string(nivel * 4, ' ') << description();
    return s.str();
}
#include "Weapon.h"
#include <sstream>
// --------------- Methods ---------------
Weapon::Weapon() {
    name = "WEAPON'S";
}
std::string Weapon::getName() const {
    return name;
}
void Weapon::add(Item* element) {
    weapons.push_back(element);
}
std::string Weapon::toString(int nivel = 0) {
    std::stringstream s;
    s << std::string(nivel * 3, '-') << "[" << name << "] \n";
    for (auto w : weapons) {
        s << "|" << w->toString(nivel + 1);
    }
    return s.str();
}
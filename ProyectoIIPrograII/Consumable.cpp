#include "Consumable.h"
#include <sstream>
// --------------- Methods ---------------
Consumable::Consumable() {
    name = "CONSUMABLE'S";
}
std::string Consumable::getName() const {
    return name;
}
void Consumable::add(Item* element) {
    consumables.push_back(element);
}
std::string Consumable::toString(int nivel = 0) {
    std::stringstream s;
    s << std::string(nivel * 3, '-') << "[" << name << "] \n";
    for (auto c : consumables) {
        s << "|" << c->toString(nivel + 1);
    }
    return s.str();
}
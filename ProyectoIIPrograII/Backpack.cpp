#include "Backpack.h"
#include <sstream>
Backpack::Backpack() {
    name = "BACKPACK";
}
std::string Backpack::getName() const {
    return name;
}
void Backpack::add(Item* element) {
    items.push_back(element);
}
std::string Backpack::toString(int nivel = 0) {
    std::stringstream s;
    s << "|" << std::string(nivel * 2, '-') << "[" << name << "] \n";
    for (auto i : items) {
        s << "|" << i->toString(nivel + 1);
    }
    return s.str();
}
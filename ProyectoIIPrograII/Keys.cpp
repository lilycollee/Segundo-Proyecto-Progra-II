#include "Keys.h"
#include <sstream>
// --------------- Methods ---------------
Keys::Keys() {
    name = "KEY'S";
}
std::string Keys::getName() const {
    return name;
}
void Keys::add(Item* element) {
    keys.push_back(element);
}
std::string Keys::toString(int nivel = 0) {
    std::stringstream s;
    s << std::string(nivel * 3, '-') << "[" << name << "] \n";
    for (auto k : keys) {
        s << "|" << k->toString(nivel + 1);
    }
    return s.str();
}
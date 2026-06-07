#include "AccessKey.h"
#include <sstream>
AccessKey::AccessKey(std::string name) {
    this->name = name;
}
std::string AccessKey::getName() const {
    return name;
}
std::string AccessKey::description() {
    std::stringstream s;
    s << "DESCRIPTION: " << name << " | Quick access key for emergencies {o--¬} \n";
    return s.str();
}
std::string AccessKey::toString(int nivel = 0) {
    std::stringstream s;
    s << std::string(nivel * 3, ' ') << "[KEY]\n";
    s << "|" << std::string(nivel * 4, ' ') << description();
    return s.str();
}
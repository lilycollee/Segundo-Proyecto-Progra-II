#include "DeactivationKey.h"
#include <sstream>
DeactivationKey::DeactivationKey() {
    name = "Master Key For Androids";
}
std::string DeactivationKey::getName() const {
    return name;
}
std::string DeactivationKey::description() {
    std::stringstream s;
    s << "DESCRIPTION: " << name << " | Use to deactivate androids !!!\n";
    return s.str();
}
std::string DeactivationKey::toString(int nivel = 0) {
    std::stringstream s;
    s << std::string(nivel * 3, ' ') << "[DEACTIVATION KEY]\n";
    s << "|" << std::string(nivel * 4, ' ') << description();
    return s.str();
}
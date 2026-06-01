#include "LaserGun.h"
#include <sstream>
LaserGun::LaserGun() {
    name = "Long-range Laser Gun";
}
std::string LaserGun::getName() const {
    return name;
}
std::string LaserGun::description() {
    std::stringstream s;
    s << "DESCRIPTION: " << name << " | Special weapon to use with the final boss !!!\n";
    return s.str();
}
std::string LaserGun::toString(int nivel = 0) {
    std::stringstream s;
    s << std::string(nivel * 3, ' ') << "[LASER GUN]\n";
    s << "|" << std::string(nivel * 4, ' ') << description();
    return s.str();
}
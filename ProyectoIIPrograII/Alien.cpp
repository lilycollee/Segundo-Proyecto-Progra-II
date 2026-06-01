#include "Alien.h"

Alien::Alien() {
    name = "Final boss: Alien";
    health = 100;
}

Alien::~Alien() {}

double Alien::getHealth() const { return health; }

std::string Alien::getName() const { return name; }

std::string Alien::showEntity() const {
    char c = char(248);
    std::stringstream ss;
    ss << " :-----:" << std::endl;
    ss << " { " << c << ' ' << c <<" }" << std::endl;
    ss << " (     ) " << std::endl;
    ss << " ^^^ ^^^ ";

    return ss.str();
}

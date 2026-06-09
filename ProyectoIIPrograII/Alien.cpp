#include "Alien.h"
#include <random>
#include <ctime>

Alien::Alien() {
    name = "Alien";
    health = 120;
}

Alien::~Alien() {}

Alien& Alien::getInstance() {
    static Alien instance;
    return instance;
}

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

double Alien::attack() {
    // The boss hits harder than the androids
    static std::mt19937 gen(std::time(nullptr));
    std::uniform_real_distribution<double> dist(25, 35);
    return dist(gen);
}

void Alien::lowerHealth(double damage) {
    health -= damage;
    if (health < 0) health = 0;
}

bool Alien::isDefeated() const {
    return health <= 0;
}

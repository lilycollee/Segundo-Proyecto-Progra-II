#include <random>
#include <ctime>
#include "Androide.h"



Androide::Androide(std::string name_) : name(name_) {
    damage = 0;
    inOff = true;
}

Androide::~Androide() {};

void Androide::turnOff() { inOff = false; }

double Androide::getDamage() const { return damage; }
void Androide::setDamage(double damage_) { damage = damage_; }

void Androide::hurt(double& damage) {
    static std::mt19937 gen(std::time(nullptr));
    std::uniform_real_distribution<double> dist(0.01, 0.99);
    damage = dist(gen);
}

std::string Androide::getName() const { return name; }
std::string Androide::showEntity() const {
    char c = char(248);
    std::stringstream ss;
    ss<< "  (" << c << ") " << std::endl;
    ss<<R"( /| |\)" << std::endl;
    ss<<"  ^ ^" << std::endl;

    return ss.str();

}

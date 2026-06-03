#include "Player.h"
Player::Player() {
    name = "SpaceMan";
    energy = 100;
    oxygen = 100;
}

Player::Player(std::string name) : name(name) {
    energy = 100;
    oxygen = 100;
}
Player::~Player() {
    std::cout << name << " is dead!! X_X" << std::endl;
}

int Player::getEnergy() const  { return energy; }
void Player::setEnergy(int energy) { this->energy = energy; }

double Player::getOxygen() const  { return oxygen; }
void Player::setOxygen(int oxygen) { this->oxygen = oxygen; }

std::string Player::showInformation() const {
    std::stringstream ss;
    ss << name << " has: \n";
    ss << "Energy: " << energy << "%\n" ;
    ss << "Oxygen: " << oxygen << "%\n";
    return ss.str();
}

std::string Player::getName() const  { return name; }
void Player::setName(std::string name) { this->name = name; }

std::string Player::showEntity() const {
    std::stringstream ss;
    ss << R"(   (") )" << std::endl;
    ss << "   -|-" << std::endl;
    ss << R"(   / \)";
    return ss.str();
}

void Player::refillOxygen(OxygenTank* oxy) {
    if (oxygen < 80) {
        //usar item
            //baja la capacidad del tanque y lo desactiva
        oxygen > 60 ? oxygen = 100 : oxygen+= 40;
        oxy->setActive(false);
    }
}


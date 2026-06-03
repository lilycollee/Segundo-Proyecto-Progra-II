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

void Player::refillOxygen(OxygenTank* oxyT) {
    if (oxygen < 80) {
        if (oxyT->getActive()) {
        	oxygen+oxyT->getCapacity() > 100?
				oxygen = 100 : oxygen+=oxyT->getCapacity();

        	oxyT->setActive(false); //deshabilita el tanque
			oxyT->setCapacity(0);
		}
		//el tanque de oxigeno ya ha sido usado
    }
	//el oxigeno es alto, evito desperdicio
}

void Player::useMedicalKit(MedicalEquipment* kit) {
    if (energy < 90) {
        if (kit->getActive()) {
            energy + kit->getCapacity() > 100 ?
				energy = 100 : energy += kit->getCapacity();
            kit->setActive(false); // el kit ya fue usado
			kit->setCapacity(0);
        }
		//el kit ya fue usado
    }
	//tiene suficiente energia, evita desperdicio
}


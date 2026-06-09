#include <algorithm>
#include "Player.h"
Player::Player() {
    name = "SpaceMan";
    energy = 100;
    oxygen = 100;
    myBackPack = std::make_unique<Backpack>();
    myBackPack->add(new OxygenTank("Oxygen Tank",30));
}
Player::Player(std::string name_) : name(name_) {
    energy = 100;
    oxygen = 100;
    myBackPack = std::make_unique<Backpack>();
    myBackPack->add(new OxygenTank("Oxygen Tank",30));
}
Player::~Player() {
    std::cout << name << " is dead!! X_X" << std::endl;
}
int Player::getEnergy() const  { return energy; }
void Player::setEnergy(int e) {
    this->energy = e;
    notify("ENERGY_CHANGED", energy);
    if (energy <= 0) {
        notify("PLAYER_DEAD");
    }
}
double Player::getOxygen() const  { return oxygen; }
void Player::setOxygen(int o) {
    this->oxygen = o;
    notify("OXYGEN_CHANGED", oxygen);
    if (oxygen <= 0) {
        notify("PLAYER_DEAD");
    }
}
std::string Player::showInformation() const {
    std::stringstream ss;
    ss << name << " has: \n";
    ss << "Energy: " << energy << "%\n" ;
    ss << "Oxygen: " << oxygen << "%\n";
    return ss.str();
}
std::string Player::getName() const  { return name; }
void Player::setName(std::string name_) { this->name = name_; }
std::string Player::showEntity() const {
    std::stringstream ss;
    ss << R"(   (") )" << std::endl;
    ss << "   -|-" << std::endl;
    ss << R"(   / \)";
    return ss.str();
}
void Player::refillOxygen(OxygenTank* oxyT) {
    if (oxygen < 75) {
        if (oxyT->getActive()) {
            if (oxygen + oxyT->getCapacity() > 100) {
                oxygen = 100;
            } else {
                oxygen += oxyT->getCapacity();
            }
        	oxyT->setActive(false); //deshabilita el tanque
			oxyT->setCapacity(0);
		}
		//el tanque de oxigeno ya ha sido usado
    }
	//el oxigeno es alto, evito desperdicio
}
void Player::useMedicalKit(MedicalEquipment* kit) {
    if (energy < 75) {
        if (kit->getActive()) {
            if (energy + kit->getCapacity() > 100) {
                energy = 100 ;
            } else {
                energy += kit->getCapacity();
            }
            kit->setActive(false); // el kit ya fue usado
			kit->setCapacity(0);
        }
		//el kit ya fue usado
    }
	//tiene suficiente energia, evita desperdicio
}
void Player::pickUpItem(Item *item) {
    myBackPack->add(item);
}
std::string Player::showInventory() const {
    return myBackPack->toString(0);
}
void Player::addObserver(IObserver* obs) {
    observers.push_back(obs);
}
void Player::removeObserver(IObserver* obs) {
    observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
}
void Player::notify(const std::string& event, double value) {
    for (auto* obs : observers) {
        obs->onEvent(event, value);
    }
}